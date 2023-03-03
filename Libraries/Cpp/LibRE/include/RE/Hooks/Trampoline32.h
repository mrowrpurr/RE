#pragma once

#include <Windows.h>

#include "RE/Hooks/Detour32.h"

namespace RE::Hooks {

    BYTE popad = 0x61;

    BYTE* CrazyTrampolineHook32(BYTE* src, BYTE* dst, const uintptr_t len = 6) {
        if (len < 5) return 0;

        BYTE* gateway = (BYTE*)VirtualAlloc(0, len + 6, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

        memcpy_s(gateway, 1, (BYTE*)&popad, 1);
        memcpy_s(gateway + 1, len, src, len);

        uintptr_t gatewayRelativeAddress = src - gateway - 5 - 1;

        *(gateway + len + 1)                            = 0xE9;
        *(uintptr_t*)((uintptr_t)gateway + len + 1 + 1) = gatewayRelativeAddress;

        PushFirstDetour32(src, dst);

        return gateway;
    }

    BYTE* TrampolineHook32(BYTE* src, BYTE* dst, const uintptr_t len) {
        if (len < 5) return 0;
        BYTE* gateway = (BYTE*)VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        memcpy_s(gateway, len, src, len);
        uintptr_t gatewayRelativeAddress            = src - gateway - 5;
        *(gateway + len)                            = 0xE9;
        *(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddress;
        Detour32(src, dst, len);
        return gateway;
    }
}