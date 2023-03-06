#pragma once

#include <cstdint>
#include <vector>

#include "Hooks/MemoryBytes.h"

namespace Hooks::Registers {

    namespace Current {
        uint32_t EAX = 0;
        uint32_t EBX = 0;
        uint32_t ECX = 0;
        uint32_t EDX = 0;
        uint32_t ESI = 0;
        uint32_t EDI = 0;
        uint32_t EBP = 0;
        uint32_t ESP = 0;
    }

    namespace Instructions {

        namespace Save {
            std::vector<uint8_t> EAX = {0xA3};
            std::vector<uint8_t> EBX = {0x89, 0x1D};
            std::vector<uint8_t> ECX = {0x89, 0x0D};
            std::vector<uint8_t> EDX = {0x89, 0x15};
            std::vector<uint8_t> ESI = {0x89, 0x35};
            std::vector<uint8_t> EDI = {0x89, 0x3D};
            std::vector<uint8_t> EBP = {0x89, 0x2D};
            std::vector<uint8_t> ESP = {0x89, 0x25};
        }

        namespace Restore {
            std::vector<uint8_t> EAX = {0x8B, 0x05};
            std::vector<uint8_t> EBX = {0x8B, 0x1D};
            std::vector<uint8_t> ECX = {0x8B, 0x0D};
            std::vector<uint8_t> EDX = {0x8B, 0x15};
            std::vector<uint8_t> ESI = {0x8B, 0x35};
            std::vector<uint8_t> EDI = {0x8B, 0x3D};
            std::vector<uint8_t> EBP = {0x8B, 0x2D};
            std::vector<uint8_t> ESP = {0x8B, 0x25};
        }

        void WriteSaveBytes(MemoryBytes& trampoline) {
            trampoline.WriteBytes(Save::EAX);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::EAX));
            trampoline.WriteBytes(Save::EBX);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::EBX));
            trampoline.WriteBytes(Save::ECX);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::ECX));
            trampoline.WriteBytes(Save::EDX);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::EDX));
            trampoline.WriteBytes(Save::ESI);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::ESI));
            trampoline.WriteBytes(Save::EDI);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::EDI));
            trampoline.WriteBytes(Save::EBP);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::EBP));
            trampoline.WriteBytes(Save::ESP);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::ESP));
        }

        void WriteRestoreBytes(MemoryBytes& trampoline) {
            trampoline.WriteBytes(Restore::EAX);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::EAX));
            trampoline.WriteBytes(Restore::EBX);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::EBX));
            trampoline.WriteBytes(Restore::ECX);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::ECX));
            trampoline.WriteBytes(Restore::EDX);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::EDX));
            trampoline.WriteBytes(Restore::ESI);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::ESI));
            trampoline.WriteBytes(Restore::EDI);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::EDI));
            trampoline.WriteBytes(Restore::EBP);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::EBP));
            trampoline.WriteBytes(Restore::ESP);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::ESP));
        }
    }

    class RegistersReader {
        RegistersReader()                                  = default;
        ~RegistersReader()                                 = default;
        RegistersReader(const RegistersReader&)            = delete;
        RegistersReader(RegistersReader&&)                 = delete;
        RegistersReader& operator=(const RegistersReader&) = delete;
        RegistersReader& operator=(RegistersReader&&)      = delete;

    public:
        static RegistersReader& Current() {
            static RegistersReader singleton;
            return singleton;
        }

        uint32_t eax() { return Current::EAX; }

        template <typename T>
        T eax() {
            return (T)Current::EAX;
        }

        template <typename T>
        T eax(uint32_t offset) {
            return *reinterpret_cast<T*>(Current::EAX + offset);
        }

        template <typename T>
        T eax(std::vector<uint32_t> offsets) {
            uint32_t address = Current::EAX;
            for (size_t i = 0; i < offsets.size() - 1; i++)
                address = *reinterpret_cast<uint32_t*>(address + offsets[i]);
            return *reinterpret_cast<T*>(address + offsets.back());
        }

        uint32_t ebx() { return Current::EBX; }

        template <typename T>
        T ebx() {
            return (T)Current::EBX;
        }

        template <typename T>
        T ebx(uint32_t offset) {
            return *reinterpret_cast<T*>(Current::EBX + offset);
        }

        template <typename T>
        T ebx(std::vector<uint32_t> offsets) {
            uint32_t address = Current::EBX;
            for (size_t i = 0; i < offsets.size() - 1; i++)
                address = *reinterpret_cast<uint32_t*>(address + offsets[i]);
            return *reinterpret_cast<T*>(address + offsets.back());
        }

        uint32_t ecx() { return Current::ECX; }

        template <typename T>
        T ecx() {
            return (T)Current::ECX;
        }

        template <typename T>
        T ecx(uint32_t offset) {
            return *reinterpret_cast<T*>(Current::ECX + offset);
        }

        template <typename T>
        T ecx(std::vector<uint32_t> offsets) {
            uint32_t address = Current::ECX;
            for (size_t i = 0; i < offsets.size() - 1; i++)
                address = *reinterpret_cast<uint32_t*>(address + offsets[i]);
            return *reinterpret_cast<T*>(address + offsets.back());
        }

        uint32_t edx() { return Current::EDX; }

        template <typename T>
        T edx() {
            return (T)Current::EDX;
        }

        template <typename T>
        T edx(uint32_t offset) {
            return *reinterpret_cast<T*>(Current::EDX + offset);
        }

        template <typename T>
        T edx(std::vector<uint32_t> offsets) {
            uint32_t address = Current::EDX;
            for (size_t i = 0; i < offsets.size() - 1; i++)
                address = *reinterpret_cast<uint32_t*>(address + offsets[i]);
            return *reinterpret_cast<T*>(address + offsets.back());
        }

        uint32_t esi() { return Current::ESI; }

        template <typename T>
        T esi() {
            return (T)Current::ESI;
        }

        template <typename T>
        T esi(uint32_t offset) {
            return *reinterpret_cast<T*>(Current::ESI + offset);
        }

        template <typename T>
        T esi(std::vector<uint32_t> offsets) {
            uint32_t address = Current::ESI;
            for (size_t i = 0; i < offsets.size() - 1; i++)
                address = *reinterpret_cast<uint32_t*>(address + offsets[i]);
            return *reinterpret_cast<T*>(address + offsets.back());
        }

        uint32_t edi() { return Current::EDI; }

        template <typename T>
        T edi() {
            return (T)Current::EDI;
        }

        template <typename T>
        T edi(uint32_t offset) {
            return *reinterpret_cast<T*>(Current::EDI + offset);
        }

        template <typename T>
        T edi(std::vector<uint32_t> offsets) {
            uint32_t address = Current::EDI;
            for (size_t i = 0; i < offsets.size() - 1; i++)
                address = *reinterpret_cast<uint32_t*>(address + offsets[i]);
            return *reinterpret_cast<T*>(address + offsets.back());
        }

        uint32_t ebp() { return Current::EBP; }

        template <typename T>
        T ebp() {
            return (T)Current::EBP;
        }

        template <typename T>
        T ebp(uint32_t offset) {
            return *reinterpret_cast<T*>(Current::EBP + offset);
        }

        template <typename T>
        T ebp(std::vector<uint32_t> offsets) {
            uint32_t address = Current::EBP;
            for (size_t i = 0; i < offsets.size() - 1; i++)
                address = *reinterpret_cast<uint32_t*>(address + offsets[i]);
            return *reinterpret_cast<T*>(address + offsets.back());
        }

        uint32_t esp() { return Current::ESP; }

        template <typename T>
        T esp() {
            return (T)Current::ESP;
        }

        template <typename T>
        T esp(uint32_t offset) {
            return *reinterpret_cast<T*>(Current::ESP + offset);
        }

        template <typename T>
        T esp(std::vector<uint32_t> offsets) {
            uint32_t address = Current::ESP;
            for (size_t i = 0; i < offsets.size() - 1; i++)
                address = *reinterpret_cast<uint32_t*>(address + offsets[i]);
            return *reinterpret_cast<T*>(address + offsets.back());
        }
    };
}
