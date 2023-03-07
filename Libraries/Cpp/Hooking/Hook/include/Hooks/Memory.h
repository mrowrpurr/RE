#pragma once

#include <Logging.h>
#include <Windows.h>

#include <stdexcept>
#include <vector>

#include "Hooks/Bytes.h"

namespace Hooks::Memory {
    Bytes ReadBytes(uint32_t address, uint32_t length) {
        Bytes bytes{};
        for (uint32_t i = 0; i < length; i++)
            bytes.WriteByte(*reinterpret_cast<uint8_t*>(address + i));
        return bytes;
    }

    void FreeBytes(uint32_t address) {
        if (!VirtualFree(reinterpret_cast<BYTE*>(address), 0, MEM_RELEASE))
            throw std::runtime_error("Failed to free memory");
        Log("Freed bytes at {:x}", address);
    }

    void WriteByte(uint32_t address, uint8_t byte) {
        *reinterpret_cast<uint8_t*>(address) = byte;
        Log("Write 0x{:x}: {:x}", address, byte);
    }
    void WriteBytes(uint32_t address, const std::vector<uint8_t>& bytes) {
        for (uint32_t i = 0; i < bytes.size(); i++) WriteByte(address + i, bytes[i]);
    }
    void WriteNops(uint32_t address, uint32_t length) {
        for (uint32_t i = 0; i < length; i++) WriteByte(address + i, 0x90);
    }

    void Protected(uint32_t address, uint32_t byteCount, std::function<void()> code) {
        DWORD oldProtect;
        VirtualProtect(
            reinterpret_cast<BYTE*>(address), byteCount, PAGE_EXECUTE_READWRITE, &oldProtect
        );
        code();
        VirtualProtect(reinterpret_cast<BYTE*>(address), byteCount, oldProtect, &oldProtect);
    }
    void WriteProtectedBytes(uint32_t address, const std::vector<uint8_t>& bytes) {
        Protected(address, bytes.size(), [&]() { WriteBytes(address, bytes); });
    }
    void WriteProtectedByte(uint32_t address, uint8_t byte) {
        Protected(address, 1, [&]() { WriteByte(address, byte); });
    }
    void WriteProtectedNops(uint32_t address, uint32_t length) {
        Protected(address, length, [&]() { WriteNops(address, length); });
    }

    uint32_t AllocateBytes(uint32_t length) {
        // HACK TODO FIXME BLAH I HATE THIS...
        length = 255;
        // if (length == 0) throw std::runtime_error("Length cannot be 0");
        auto addressPtr =
            VirtualAlloc(nullptr, length, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (addressPtr == nullptr) throw std::runtime_error("Failed to allocate memory");
        auto address = reinterpret_cast<uint32_t>(addressPtr);
        Log("Allocated {} bytes at {:x}", length, address);
        return address;
    }
    uint32_t AllocateBytes(const std::vector<uint8_t>& bytes) {
        auto address = AllocateBytes(bytes.size());
        WriteBytes(address, bytes);
        return address;
    }
}
