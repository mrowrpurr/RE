#pragma once

#include "Memory/Bytes.h"

namespace Memory {

    class MemoryReader {
        uintptr_t _address;

    public:
        MemoryReader(uintptr_t address) : _address(address) {}
        MemoryReader(const MemoryAddress& address) : _address(address.GetAddress()) {}
        MemoryReader() : _address(0) {}

        Bytes Read(size_t size) const {
            Bytes bytes;
            for (size_t i = 0; i < size; i++) bytes.WriteByte(*(uint8_t*)(_address + i));
            return bytes;
        }
        Bytes Read() const { return Read(1); }

        template <typename T>
        T Read() const {
            return *(T*)_address;
        }

        template <typename T>
        T Read(uintptr_t offset) const {
            return *(T*)(_address + offset);
        }

        template <typename T>
        T Read(std::vector<uintptr_t> offsets) const {
            uintptr_t address = _address;
            for (auto offset : offsets) address = *(uintptr_t*)(address + offset);
            return *(T*)address;
        }
    };
}
