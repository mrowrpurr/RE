#pragma once

#include <Windows.h>

namespace RE::Hooks {

    bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len = 5) {
        if (len < 5) return false;
        DWORD curProtection;

        VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

        uintptr_t relativeAddress = dst - src - 5;

        *src = 0xE9;

        *(uintptr_t*)((uintptr_t)src + 1) = relativeAddress;

        // Fill the rest of the bytes with NOPs
        for (uintptr_t i = 5; i < len; i++) {
            *(src + i) = 0x90;
        }

        VirtualProtect(src, len, curProtection, &curProtection);

        return true;
    }
}
