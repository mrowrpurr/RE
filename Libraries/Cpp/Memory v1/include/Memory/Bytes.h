#pragma once

#include <string_format.h>

#include <cstdint>
#include <string>
#include <vector>

namespace Memory {

    class Bytes {
        std::vector<uint8_t> _bytes;

    public:
        Bytes() = default;
        Bytes(const std::vector<uint8_t>& bytes) : _bytes(bytes) {}

        std::vector<uint8_t>& GetBytes() { return _bytes; }

        void Write8(uint8_t byte) { _bytes.push_back(byte); }
        void WriteByte(uint8_t byte) { Write8(byte); }

        void Write16(uint16_t word) {
            _bytes.push_back(word & 0xFF);
            _bytes.push_back((word >> 8) & 0xFF);
        }
        void WriteWord(uint16_t word) { Write16(word); }

        void Write32(uint32_t dword) {
            _bytes.push_back(dword & 0xFF);
            _bytes.push_back((dword >> 8) & 0xFF);
            _bytes.push_back((dword >> 16) & 0xFF);
            _bytes.push_back((dword >> 24) & 0xFF);
        }
        // Foo bar
        void WriteDword(uint32_t dword) { Write32(dword); }

        void Write64(uint64_t qword) {
            _bytes.push_back(qword & 0xFF);
            _bytes.push_back((qword >> 8) & 0xFF);
            _bytes.push_back((qword >> 16) & 0xFF);
            _bytes.push_back((qword >> 24) & 0xFF);
            _bytes.push_back((qword >> 32) & 0xFF);
            _bytes.push_back((qword >> 40) & 0xFF);
            _bytes.push_back((qword >> 48) & 0xFF);
            _bytes.push_back((qword >> 56) & 0xFF);
        }
        void WriteQword(uint64_t qword) { Write64(qword); }

        void WriteBytes(const std::vector<uint8_t>& bytes) {
            for (auto byte : bytes) WriteByte(byte);
        }
        void WriteBytes(std::vector<uint8_t>& bytes) {
            for (auto byte : bytes) WriteByte(byte);
        }
        void WriteBytes(Bytes& bytes) { WriteBytes(bytes.GetBytes()); }

        size_t GetSize() const { return _bytes.size(); }
        void   Clear() { _bytes.clear(); }

        Bytes ReadByte() {
            Bytes bytes{};
            bytes.WriteByte(_bytes[0]);
            return bytes;
        }
        Bytes ReadBytes(size_t count) {
            Bytes bytes{};
            for (size_t i = 0; i < count; i++) {
                bytes.WriteByte(_bytes[i]);
            }
            return bytes;
        }

        Bytes operator+(const Bytes& other) {
            Bytes bytes{};
            bytes.WriteBytes(_bytes);
            bytes.WriteBytes(other._bytes);
            return bytes;
        }
        Bytes operator+(const std::vector<uint8_t>& other) {
            Bytes bytes{};
            bytes.WriteBytes(_bytes);
            bytes.WriteBytes(other);
            return bytes;
        }
        Bytes operator+(const uint8_t other) {
            Bytes bytes{};
            bytes.WriteBytes(_bytes);
            bytes.WriteByte(other);
            return bytes;
        }
        Bytes operator+(const uint16_t other) {
            Bytes bytes{};
            bytes.WriteBytes(_bytes);
            bytes.WriteWord(other);
            return bytes;
        }
        Bytes operator+(const uint32_t other) {
            Bytes bytes{};
            bytes.WriteBytes(_bytes);
            bytes.WriteDword(other);
            return bytes;
        }
        Bytes operator+(const uint64_t other) {
            Bytes bytes{};
            bytes.WriteBytes(_bytes);
            bytes.WriteQword(other);
            return bytes;
        }

        Bytes& operator+=(const Bytes& other) {
            WriteBytes(other._bytes);
            return *this;
        }
        Bytes& operator+=(const std::vector<uint8_t>& other) {
            WriteBytes(other);
            return *this;
        }
        Bytes& operator+=(const uint8_t other) {
            WriteByte(other);
            return *this;
        }
        Bytes& operator+=(const uint16_t other) {
            WriteWord(other);
            return *this;
        }
        Bytes& operator+=(const uint32_t other) {
            WriteDword(other);
            return *this;
        }
        Bytes& operator+=(const uint64_t other) {
            WriteQword(other);
            return *this;
        }

        uint8_t operator[](size_t index) const { return _bytes[index]; }

        const std::string Encode() const { return ToString(); }
        const std::string ToHex() const {
            std::string encoded{};
            for (size_t i = 0; i < _bytes.size(); i++) {
                encoded += string_format("{:x}", _bytes[i]);
                if (i != _bytes.size() - 1) encoded += " ";
            }
            return encoded;
        }
        const std::string ToString() const { return ToHex(); }

        operator std::string() const { return ToString(); }

        static Bytes FromString(const std::string& string) {
            Bytes bytes{};
            for (auto c : string) bytes.WriteByte(c);
            return bytes;
        }
        static Bytes Decode(const std::string& string) { return FromString(string); }
    };
}