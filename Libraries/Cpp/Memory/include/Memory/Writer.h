#pragma once

#include <Logging.h>
#include <StringFormatting.h>
#include <Windows.h>

#include <cstdint>

#include "Bytes.h"

namespace Memory {

    void Write(uintptr_t address, const std::vector<uint8_t>& bytes) {
        Log("Writing {} bytes to address {:x}", bytes.size(), address);
        if (bytes.size() < 128) Log(Bytes{bytes}.ToHexString());
        for (size_t i = 0; i < bytes.size(); i++) *(uint8_t*)(address + i) = bytes[i];
    }

    void WriteProtected(uintptr_t address, const std::vector<uint8_t>& bytes) {
        Log("Writing {} protected bytes to address {:x}", bytes.size(), address);
        if (bytes.size() < 128) Log(Bytes{bytes}.ToHexString());
        DWORD oldProtect;
        VirtualProtect((void*)address, bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy((void*)address, bytes.data(), bytes.size());
        VirtualProtect((void*)address, bytes.size(), oldProtect, &oldProtect);
    }

    uintptr_t Allocate(size_t size) {
        Log("Allocating {} bytes", size);
        auto addressPtr = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (addressPtr == nullptr) throw std::runtime_error("Failed to allocate memory");
        auto address = reinterpret_cast<uintptr_t>(addressPtr);
        Log("Allocated at address {:x}", address);
        return address;
    }

    void Free(uintptr_t address) {
        Log("Freeing memory at address {:x}", address);
        if (VirtualFree((void*)address, 0, MEM_RELEASE)) Log("Freed memory at address {:x}", address);
        else throw std::runtime_error(string_format("Failed to free memory at address {:x}", address));
    }
}
