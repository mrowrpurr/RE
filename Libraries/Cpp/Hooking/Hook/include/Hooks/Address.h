#pragma once

#include <cstdint>
#include <vector>

namespace Hooks {

    class Address {
        uint32_t _address;

    public:
        Address() : _address(0) {}
        Address(uint32_t address) : _address(address) {}
        Address(uint32_t address, uint32_t offset)
            : _address(*reinterpret_cast<uint32_t*>(address + offset)) {}
        Address(uint32_t address, std::vector<uint32_t> offsets) {
            _address = address;
            for (auto offset : offsets) _address = *reinterpret_cast<uint32_t*>(_address + offset);
        }

        uint32_t GetAddress() { return _address; }

        Address Get() { return Address{_address}; }

        template <typename T>
        T As() {
            return (T)_address;
        }

        template <typename T>
        T Get() {
            return (T)_address;
        }

        Address Get(uint32_t offset) {
            return Address{*reinterpret_cast<uint32_t*>(_address + offset)};
        }

        Address Get(std::vector<uint32_t> offsets) {
            auto address = _address;
            for (size_t i = 0; i < offsets.size() - 1; i++)
                address = *reinterpret_cast<uint32_t*>(address + offsets[i]);
            return Address{address + offsets.back()};
        }

        template <typename T>
        T Get(uint32_t offset) {
            return reinterpret_cast<T>(_address + offset);
        }

        template <typename T>
        T Get(std::vector<uint32_t> offsets) {
            auto address = _address;
            for (size_t i = 0; i < offsets.size() - 1; i++)
                address = *reinterpret_cast<uint32_t*>(address + offsets[i]);
            return reinterpret_cast<T>(address + offsets.back());
        }

        template <typename T>
        std::array<T, 256> GetArray() {
            std::array<T, 256> array;
            for (size_t i = 0; i < array.size(); i++)
                array[i] = *reinterpret_cast<T*>(_address + i);
            return array;
        }
        template <typename T, std::size_t size>
        std::array<T, size> GetArray() {
            std::array<T, size> array;
            for (size_t i = 0; i < array.size(); i++)
                array[i] = *reinterpret_cast<T*>(_address + i);
            return array;
        }
        template <typename T>
        std::array<T, 256> GetArray(uint32_t offset) {
            auto               address = Get(offset);
            std::array<T, 256> array;
            for (size_t i = 0; i < array.size(); i++)
                array[i] = *reinterpret_cast<T*>(_address + i);
            return array;
        }
        template <typename T, std::size_t size>
        std::array<T, size> GetArray(uint32_t offset) {
            auto                address = Get(offset);
            std::array<T, size> array;
            for (size_t i = 0; i < array.size(); i++)
                array[i] = *reinterpret_cast<T*>(_address + i);
            return array;
        }
        template <typename T>
        std::array<T, 256> GetArray(std::vector<uint32_t> offsets) {
            auto               address = Get(offsets);
            std::array<T, 256> array;
            for (size_t i = 0; i < array.size(); i++) array[i] = *reinterpret_cast<T*>(address + i);
            return array;
        }
        template <typename T, std::size_t size>
        std::array<T, size> GetArray(std::vector<uint32_t> offsets) {
            auto                address = Get(offsets);
            std::array<T, size> array;
            for (size_t i = 0; i < array.size(); i++) array[i] = *reinterpret_cast<T*>(address + i);
            return array;
        }

        Address operator()() { return Get(); }
        Address operator()(uint32_t offset) { return Get(offset); }
        Address operator()(std::vector<uint32_t> offsets) { return Get(offsets); }
        template <typename T>
        T operator()() {
            return Get<T>();
        }
        template <typename T>
        T operator()(uint32_t offset) {
            return Get<T>(offset);
        }
        template <typename T>
        T operator()(std::vector<uint32_t> offsets) {
            return Get<T>(offsets);
        }

        Address operator[](uint32_t offset) { return Get(offset); }
        Address operator[](std::vector<uint32_t> offsets) { return Get(offsets); }
        template <typename T>
        T operator[](uint32_t offset) {
            return Get<T>(offset);
        }
        template <typename T>
        T operator[](std::vector<uint32_t> offsets) {
            return Get<T>(offsets);
        }

        operator uint32_t() { return _address; }
    };
}
