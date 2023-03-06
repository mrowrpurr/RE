#pragma once

#include <Logging.h>
#include <Windows.h>

#include <stdexcept>
#include <vector>

#include "Hooks/Bytes.h"

namespace Hooks::Memory {

    uint32_t AllocateBytes(uint32_t length) {
        if (length == 0) throw std::runtime_error("Length cannot be 0");
        auto address =
            VirtualAlloc(nullptr, length, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (address == nullptr) throw std::runtime_error("Failed to allocate memory");
        return reinterpret_cast<uint32_t>(address);
    }

    void FreeBytes(uint32_t address, uint32_t length) {
        if (!VirtualFree(reinterpret_cast<BYTE*>(address), length, MEM_RELEASE))
            throw std::runtime_error("Failed to free memory");
    }

    void WriteBytes(uint32_t address, const std::vector<uint8_t>& bytes) {
        memcpy_s(reinterpret_cast<BYTE*>(address), bytes.size(), bytes.data(), bytes.size());
        for (uint32_t i = 0; i < bytes.size(); i++)
            Log("memcpy_s 0x{:x}: {:x}", address + i, bytes[i]);
    }

    void WriteByte(uint32_t address, uint8_t byte) {
        memcpy_s(reinterpret_cast<BYTE*>(address), 1, &byte, 1);
        Log("memcpy_s 0x{:x}: {:x}", address, byte);
    }

    void FreeProtectedBytes(uint32_t address, uint32_t length) {
        DWORD oldProtect;
        VirtualProtect(
            reinterpret_cast<BYTE*>(address), length, PAGE_EXECUTE_READWRITE, &oldProtect
        );
        FreeBytes(address, length);
        VirtualProtect(reinterpret_cast<BYTE*>(address), length, oldProtect, &oldProtect);
    }

    void WriteProtectedBytes(uint32_t address, const std::vector<uint8_t>& bytes) {
        DWORD oldProtect;
        VirtualProtect(
            reinterpret_cast<BYTE*>(address), bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect
        );
        WriteBytes(address, bytes);
        VirtualProtect(reinterpret_cast<BYTE*>(address), bytes.size(), oldProtect, &oldProtect);
    }

    void WriteProtectedByte(uint32_t address, uint8_t byte) {
        DWORD oldProtect;
        VirtualProtect(reinterpret_cast<BYTE*>(address), 1, PAGE_EXECUTE_READWRITE, &oldProtect);
        WriteByte(address, byte);
        VirtualProtect(reinterpret_cast<BYTE*>(address), 1, oldProtect, &oldProtect);
    }

    Bytes ReadBytes(uint32_t address, uint32_t length) {
        Bytes bytes{};
        for (uint32_t i = 0; i < length; i++)
            bytes.WriteByte(*reinterpret_cast<uint8_t*>(address + i));
        return bytes;
    }

    uint32_t AllocateBytes(const std::vector<uint8_t>& bytes) {
        auto address = AllocateBytes(bytes.size());
        WriteBytes(address, bytes);
        return address;
    }
}
