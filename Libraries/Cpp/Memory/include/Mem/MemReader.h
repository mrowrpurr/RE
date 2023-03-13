#pragma once

#include <cstdint>
#include <vector>

namespace Mem {

    class MemoryReader {
        uintptr_t _address = 0;

    public:
        MemoryReader() = default;
        MemoryReader(uintptr_t address) : _address(address) {}

        void      SetAddress(uintptr_t address) { _address = address; }
        uintptr_t GetAddress() const { return _address; }

        std::vector<uint8_t> Read(size_t size) const {
            std::vector<uint8_t> bytes(size);
            for (size_t i = 0; i < size; i++) bytes[i] = *reinterpret_cast<uint8_t*>(_address + i);
            return bytes;
        }
    };
}
