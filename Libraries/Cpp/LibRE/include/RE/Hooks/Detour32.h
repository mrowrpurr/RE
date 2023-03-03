#pragma once

#include <Windows.h>

namespace RE::Hooks {

    BYTE pushad = 0x60;

    // ..
    bool PushFirstDetour32(BYTE* src, BYTE* dst, const uintptr_t len = 6) {
        if (len < 5) return false;
        DWORD curProtection;
        VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);
        uintptr_t relativeAddress = dst - src - 6;
        *src                      = 0x60;
        src++;
        *src                              = 0xE9;
        *(uintptr_t*)((uintptr_t)src + 1) = relativeAddress;
        VirtualProtect(src, len, curProtection, &curProtection);
        return true;
    }

    bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len = 5) {
        if (len < 5) return false;
        DWORD curProtection;
        VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);
        uintptr_t relativeAddress         = dst - src - 5;
        *src                              = 0xE9;
        *(uintptr_t*)((uintptr_t)src + 1) = relativeAddress;
        VirtualProtect(src, len, curProtection, &curProtection);
        return true;
    }
}
