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

        static Bytes FromEncodedString(const std::string byteString) {
            std::vector<uint8_t> bytes;
            for (size_t i = 0; i < byteString.size(); i++) {
                if (byteString[i] == '\\') {
                    if (i + 1 >= byteString.size())
                        throw std::runtime_error(string_format("Bytes: Invalid escape sequence at index {}", i));
                    if (byteString[i + 1] == 'n') bytes.push_back('\n');
                    else if (byteString[i + 1] == 'r') bytes.push_back('\r');
                    else if (byteString[i + 1] == 't') bytes.push_back('\t');
                    else if (byteString[i + 1] == 'v') bytes.push_back('\v');
                    else if (byteString[i + 1] == 'b') bytes.push_back('\b');
                    else if (byteString[i + 1] == '\\') bytes.push_back('\\');
                    else if (byteString[i + 1] == '"') bytes.push_back('"');
                    else if (byteString[i + 1] == '\'') bytes.push_back('\'');
                    else if (byteString[i + 1] == '0') bytes.push_back('\0');
                    else if (byteString[i + 1] == 'a') bytes.push_back('\a');
                    else if (byteString[i + 1] == 'f') bytes.push_back('\f');
                    else if (byteString[i + 1] == '?') bytes.push_back('\?');
                    else if (byteString[i + 1] == 'x') {
                        if (i + 3 >= byteString.size())
                            throw std::runtime_error(string_format("Bytes: Invalid escape sequence at index {}", i));
                        std::string hex = byteString.substr(i + 2, 2);
                        bytes.push_back(static_cast<uint8_t>(std::stoi(hex, nullptr, 16)));
                        i += 2;
                    } else throw std::runtime_error(string_format("Bytes: Invalid escape sequence at index {}", i));
                    i++;
                } else bytes.push_back(byteString[i]);
            }
            return Bytes{bytes};
        }

        static Bytes FromString(const std::string& str) {
            std::vector<uint8_t> bytes;
            if (str.find(' ') != std::string::npos) return FromHexString(str);
            else return FromEncodedString(str);
        }
    };

}
