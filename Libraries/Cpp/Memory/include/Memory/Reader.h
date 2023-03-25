#pragma once

#include <StringFormatting.h>

#include <cstdint>
#include <string>
#include <vector>

namespace Memory {

    std::vector<uint8_t> Read(uintptr_t address, size_t size) {
        std::vector<uint8_t> bytes(size);
        for (size_t i = 0; i < size; i++) bytes[i] = *reinterpret_cast<uint8_t*>(address + i);
        return bytes;
    }

    template <typename T>
    T Read(uintptr_t address) {
        return (T)(address);
    }

    template <typename T>
    T Read(uintptr_t address, uint32_t offset) {
        address = *reinterpret_cast<uintptr_t*>(address + offset);
        return (T)(address);
    }

    template <typename T>
    T Read(uintptr_t address, std::vector<uint32_t> offsets) {
        for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
        return (T)(address);
    }

    // template <typename T>
    // T Read(uintptr_t address, uint32_t offset1, uint32_t offset2) {
    //     return Read<T>(address, {offset1, offset2});
    // }

    // template <typename T>
    // T Read(uintptr_t address, uint32_t offset1, uint32_t offset2, uint32_t offset3) {
    //     return Read<T>(address, {offset1, offset2, offset3});
    // }
}
