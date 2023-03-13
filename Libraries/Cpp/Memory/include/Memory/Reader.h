#pragma once

#include <cstdint>
#include <vector>

namespace Memory {

    std::vector<uint8_t> ReadBytes(uintptr_t address, size_t size) {
        std::vector<uint8_t> bytes(size);
        for (size_t i = 0; i < size; i++) bytes[i] = *reinterpret_cast<uint8_t*>(address + i);
        return bytes;
    }
}
