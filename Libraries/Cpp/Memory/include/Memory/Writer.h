#pragma once

#include <Windows.h>

#include <cstdint>

namespace Memory {

    void WriteBytes(uintptr_t address, const std::vector<uint8_t>& bytes) {
        for (size_t i = 0; i < bytes.size(); i++) {
            *(uint8_t*)(address + i) = bytes[i];
        }
    }

    void WriteProtectedBytes(uintptr_t address, const std::vector<uint8_t>& bytes) {
        DWORD oldProtect;
        VirtualProtect((void*)address, bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy((void*)address, bytes.data(), bytes.size());
        VirtualProtect((void*)address, bytes.size(), oldProtect, &oldProtect);
    }

    uintptr_t Allocate(size_t size) {
        auto address = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        return reinterpret_cast<uintptr_t>(address);
    }

    void Free(uintptr_t address) { VirtualFree((void*)address, 0, MEM_RELEASE); }
}
