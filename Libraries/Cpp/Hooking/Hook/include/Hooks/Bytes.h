#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Hooks {

    class Bytes {
        std::vector<uint8_t> _bytes;

    public:
        Bytes() = default;
        Bytes(const std::vector<uint8_t>& bytes) : _bytes(bytes) {}

        static std::string Encode(const std::vector<uint8_t>& bytes) {
            std::string encoded{};
            for (auto byte : bytes) {
                encoded += "\\x";
                encoded += std::to_string(byte);
            }
            return encoded;
        }

        std::vector<uint8_t>& GetBytes() { return _bytes; }
        void                  WriteByte(uint8_t byte) { _bytes.push_back(byte); }
        void                  WriteBytes(const std::vector<uint8_t>& bytes) {
            for (auto byte : bytes) WriteByte(byte);
        }
        void WriteBytes(std::vector<uint8_t>& bytes) {
            for (auto byte : bytes) WriteByte(byte);
        }
        void WriteBytes(Bytes& bytes) { WriteBytes(bytes.GetBytes()); }
        void WriteWord(uint16_t word) {
            _bytes.push_back(word & 0xFF);
            _bytes.push_back((word >> 8) & 0xFF);
        }
        void WriteDword(uint32_t dword) {
            _bytes.push_back(dword & 0xFF);
            _bytes.push_back((dword >> 8) & 0xFF);
            _bytes.push_back((dword >> 16) & 0xFF);
            _bytes.push_back((dword >> 24) & 0xFF);
        }

        size_t size() const { return _bytes.size(); }
        void   clear() { _bytes.clear(); }
    };
}
