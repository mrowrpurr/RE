#pragma once

#include "Hooks/Bytes.h"
#include "Hooks/Memory.h"

namespace Hooks {

    class MemoryBytes {
        uint32_t _address;
        Bytes    _bytes;

    public:
        MemoryBytes() = default;
        MemoryBytes(uint32_t address) : _address(address) {}

        uint32_t GetAddress() const { return _address; }
        Bytes&   GetBytes() { return _bytes; }
        void     SetBytes(const Bytes& bytes) { _bytes = bytes; }
        void     SetAddress(uint32_t address) { _address = address; }
        void     AddBytes(std::vector<uint8_t>& bytes) { _bytes.WriteBytes(bytes); }
        void     AddByte(uint8_t byte) { _bytes.WriteByte(byte); }
        size_t   GetSize() const { return _bytes.size(); }
        uint32_t CurrentAddress() const { return _address + _bytes.size(); }
        Bytes&   ReadBytes(size_t count) {
            if (_address == 0) throw std::runtime_error("Cannot read from address 0");
            _bytes = Memory::ReadBytes(_address, count);
            return _bytes;
        }
        void ClearBytes() { _bytes.clear(); }

        void Allocate() {
            if (GetSize() == 0) return;
            _address = Memory::AllocateBytes(_bytes.GetBytes().size());
        }
        void AllocateIfNotAllocated() {
            if (_address == 0) _address = Memory::AllocateBytes(_bytes.GetBytes().size());
        }

        void Write() {
            AllocateIfNotAllocated();
            Memory::WriteBytes(CurrentAddress(), _bytes.GetBytes());
        }
        void WriteBytes(std::vector<uint8_t>& bytes) {
            AllocateIfNotAllocated();
            Memory::WriteBytes(CurrentAddress(), bytes);
            AddBytes(bytes);
        }
        void WriteBytes(Bytes& bytes) {
            AllocateIfNotAllocated();
            Memory::WriteBytes(CurrentAddress(), bytes.GetBytes());
            AddBytes(bytes.GetBytes());
        }
        void WriteBytes(Bytes bytes) {
            AllocateIfNotAllocated();
            Memory::WriteBytes(CurrentAddress(), bytes.GetBytes());
            AddBytes(bytes.GetBytes());
        }
        void WriteByte(uint8_t byte) {
            AllocateIfNotAllocated();
            Memory::WriteByte(CurrentAddress(), byte);
            AddByte(byte);
        }
        void WriteJmp(uint32_t address) {
            AllocateIfNotAllocated();
            WriteByte(0xE9);
            auto                 relativeAddress = address + 5 - CurrentAddress() - 5;
            std::vector<uint8_t> bytes;
            bytes.push_back(relativeAddress & 0xFF);
            bytes.push_back((relativeAddress >> 8) & 0xFF);
            bytes.push_back((relativeAddress >> 16) & 0xFF);
            bytes.push_back((relativeAddress >> 24) & 0xFF);
            WriteBytes(bytes);
        }
        void WriteCall(uint32_t address) {
            AllocateIfNotAllocated();
            WriteByte(0xE8);
            auto                 relativeAddress = address + 5 - CurrentAddress() - 5;
            std::vector<uint8_t> bytes;
            bytes.push_back(relativeAddress & 0xFF);
            bytes.push_back((relativeAddress >> 8) & 0xFF);
            bytes.push_back((relativeAddress >> 16) & 0xFF);
            bytes.push_back((relativeAddress >> 24) & 0xFF);
            WriteBytes(bytes);
        }

        void WriteProtected() {
            if (_address == 0) _address = Memory::AllocateBytes(_bytes.GetBytes().size());
            Memory::WriteProtectedBytes(CurrentAddress(), _bytes.GetBytes());
        }
        void WriteProtectedBytes(std::vector<uint8_t>& bytes) {
            AllocateIfNotAllocated();
            Memory::WriteProtectedBytes(CurrentAddress(), bytes);
            AddBytes(bytes);
        }
        void WriteProtectedBytes(Bytes& bytes) {
            AllocateIfNotAllocated();
            Memory::WriteProtectedBytes(CurrentAddress(), bytes.GetBytes());
            AddBytes(bytes.GetBytes());
        }
        void WriteProtectedBytes(Bytes bytes) {
            AllocateIfNotAllocated();
            Memory::WriteProtectedBytes(CurrentAddress(), bytes.GetBytes());
            AddBytes(bytes.GetBytes());
        }
        void WriteProtectedByte(uint8_t byte) {
            AllocateIfNotAllocated();
            Memory::WriteProtectedByte(CurrentAddress(), byte);
            AddByte(byte);
        }
        void WriteProtectedJmp(uint32_t address) {
            AllocateIfNotAllocated();
            WriteProtectedByte(0xE9);                               // JMP
            auto relativeAddress = address - CurrentAddress() - 4;  // 4 is the JMP address
            std::vector<uint8_t> bytes;
            bytes.push_back(relativeAddress & 0xFF);
            bytes.push_back((relativeAddress >> 8) & 0xFF);
            bytes.push_back((relativeAddress >> 16) & 0xFF);
            bytes.push_back((relativeAddress >> 24) & 0xFF);
            WriteProtectedBytes(bytes);
        }
        void WriteProtectedCall(uint32_t address) {
            AllocateIfNotAllocated();
            WriteProtectedByte(0xE8);                               // CALL
            auto relativeAddress = address - CurrentAddress() - 4;  // 4 is the JMP address
            std::vector<uint8_t> bytes;
            bytes.push_back(relativeAddress & 0xFF);
            bytes.push_back((relativeAddress >> 8) & 0xFF);
            bytes.push_back((relativeAddress >> 16) & 0xFF);
            bytes.push_back((relativeAddress >> 24) & 0xFF);
            WriteProtectedBytes(bytes);
        }

        void Free() { Memory::FreeBytes(_address, GetSize()); }
        void FreeProtected() { Memory::FreeProtectedBytes(_address, GetSize()); }
    };
}
