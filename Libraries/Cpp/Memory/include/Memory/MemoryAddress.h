#pragma once

#include <cstdint>
#include <vector>

namespace Memory {

    class MemoryAddress {
        uintptr_t _address;

    public:
        MemoryAddress() : _address(0) {}
        MemoryAddress(uintptr_t address) : _address(address) {}

        uintptr_t GetAddress() const { return _address; }
        void      SetAddress(uintptr_t address) { _address = address; }

        MemoryAddress Offset(uintptr_t offset) const { return MemoryAddress(_address + offset); }
        MemoryAddress Offset(std::vector<uintptr_t> offsets) const {
            uintptr_t address = _address;
            for (auto offset : offsets) {
                address = *(uintptr_t*)address + offset;
            }
            return MemoryAddress(address);
        }

        MemoryAddress FollowPointer() const { return MemoryAddress(*(uintptr_t*)_address); }
        MemoryAddress FollowPointer(uintptr_t offset) const {
            return MemoryAddress(*(uintptr_t*)(_address + offset));
        }
        MemoryAddress FollowPointers(std::vector<uintptr_t> offsets) const {
            uintptr_t address = _address;
            for (auto offset : offsets) {
                address = *(uintptr_t*)address + offset;
            }
            return MemoryAddress(*(uintptr_t*)address);
        }

        MemoryAddress operator+(const MemoryAddress& other) const {
            return MemoryAddress(_address + other._address);
        }
        MemoryAddress operator-(const MemoryAddress& other) const {
            return MemoryAddress(_address - other._address);
        }
        MemoryAddress operator+(uintptr_t offset) const { return MemoryAddress(_address + offset); }
        MemoryAddress operator-(uintptr_t offset) const { return MemoryAddress(_address - offset); }
        MemoryAddress operator+=(uintptr_t offset) {
            _address += offset;
            return *this;
        }
        MemoryAddress operator-=(uintptr_t offset) {
            _address -= offset;
            return *this;
        }
        MemoryAddress operator++() {
            _address++;
            return *this;
        }
        MemoryAddress operator--() {
            _address--;
            return *this;
        }
        MemoryAddress operator++(int) {
            MemoryAddress temp = *this;
            _address++;
            return temp;
        }
        MemoryAddress operator--(int) {
            MemoryAddress temp = *this;
            _address--;
            return temp;
        }
        MemoryAddress operator&(uintptr_t mask) const { return MemoryAddress(_address & mask); }
        MemoryAddress operator|(uintptr_t mask) const { return MemoryAddress(_address | mask); }
        MemoryAddress operator&=(uintptr_t mask) {
            _address &= mask;
            return *this;
        }
        MemoryAddress operator|=(uintptr_t mask) {
            _address |= mask;
            return *this;
        }
        MemoryAddress operator~() const { return MemoryAddress(~_address); }
        MemoryAddress operator<<(uintptr_t shift) const { return MemoryAddress(_address << shift); }
        MemoryAddress operator>>(uintptr_t shift) const { return MemoryAddress(_address >> shift); }
        MemoryAddress operator<<=(uintptr_t shift) {
            _address <<= shift;
            return *this;
        }
        MemoryAddress operator>>=(uintptr_t shift) {
            _address >>= shift;
            return *this;
        }
        bool operator==(const MemoryAddress& other) const { return _address == other._address; }
        bool operator!=(const MemoryAddress& other) const { return _address != other._address; }
        bool operator<(const MemoryAddress& other) const { return _address < other._address; }
        bool operator>(const MemoryAddress& other) const { return _address > other._address; }
        bool operator<=(const MemoryAddress& other) const { return _address <= other._address; }
    };
}
