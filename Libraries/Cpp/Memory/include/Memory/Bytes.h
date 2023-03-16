#pragma once

#include <StringFormatting.h>

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace Memory {

    class Bytes {
        std::vector<uint8_t> _bytes;

    public:
        Bytes() = default;
        Bytes(std::vector<uint8_t> bytes) : _bytes(bytes) {}

        std::vector<uint8_t> GetBytes() { return _bytes; }
        size_t               GetByteCount() { return _bytes.size(); }
        size_t               size() { return GetByteCount(); }

        void AddByte(uint8_t byte) { _bytes.push_back(byte); }
        void AddBytes(std::vector<uint8_t> bytes) {
            for (auto byte : bytes) {
                _bytes.push_back(byte);
            }
        }

        void Add8(uint8_t byte) { AddByte(byte); }
        void Add16(uint16_t word) {
            _bytes.push_back((word >> 0) & 0xFF);
            _bytes.push_back((word >> 8) & 0xFF);
        }
        void Add32(uint32_t dword) {
            _bytes.push_back((dword >> 0) & 0xFF);
            _bytes.push_back((dword >> 8) & 0xFF);
            _bytes.push_back((dword >> 16) & 0xFF);
            _bytes.push_back((dword >> 24) & 0xFF);
        }
        void Add64(uint64_t qword) {
            _bytes.push_back((qword >> 0) & 0xFF);
            _bytes.push_back((qword >> 8) & 0xFF);
            _bytes.push_back((qword >> 16) & 0xFF);
            _bytes.push_back((qword >> 24) & 0xFF);
            _bytes.push_back((qword >> 32) & 0xFF);
            _bytes.push_back((qword >> 40) & 0xFF);
            _bytes.push_back((qword >> 48) & 0xFF);
            _bytes.push_back((qword >> 56) & 0xFF);
        }

        void AddWord(uint16_t word) { Add16(word); }
        void AddDword(uint32_t dword) { Add32(dword); }
        void AddQword(uint64_t qword) { Add64(qword); }

        void AddAddress(uintptr_t address) {
            if (sizeof(uintptr_t) == 4) Add32(address);
            else if (sizeof(uintptr_t) == 8) Add64(address);
            else throw std::runtime_error(string_format("Bytes: Unsupported address size {}", sizeof(uintptr_t)));
        }

        std::string ToHexString() {
            std::string str;
            for (auto byte : _bytes) str += string_format("{:x} ", byte);
            return str;
        }

        std::string ToEncodedString() {
            std::string str;
            for (auto byte : _bytes) str += string_format("\\x{:x}", byte);
            return str;
        }

        static Bytes FromHexString(const std::string& hexString) {
            std::vector<uint8_t> bytes;
            std::string          hex;
            for (auto c : hexString) {
                if (c == ' ') {
                    if (hex.empty()) continue;
                    bytes.push_back(static_cast<uint8_t>(std::stoi(hex, nullptr, 16)));
                    hex.clear();
                } else {
                    hex += c;
                }
            }
            if (!hex.empty()) bytes.push_back(static_cast<uint8_t>(std::stoi(hex, nullptr, 16)));
            return Bytes{bytes};
        }

        // TODO support escaped strings (e.g. \x00)
        static Bytes FromString(const std::string& str) { return FromHexString(str); }
    };

}
