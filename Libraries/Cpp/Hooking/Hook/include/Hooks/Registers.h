#pragma once

#include <cstdint>
#include <vector>

#include "Hooks/Address.h"
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

        Address eax() { return Address{Current::EAX}; }
        Address eax(uint32_t offset) { return Address{Current::EAX, offset}; }
        Address eax(std::vector<uint32_t> offsets) { return Address{Current::EAX, offsets}; }
        template <typename T>
        T eax() {
            return Address{Current::EAX}.Get<T>();
        }
        template <typename T>
        T eax(uint32_t offset) {
            return Address{Current::EAX, offset}.Get<T>();
        }
        template <typename T>
        T eax(std::vector<uint32_t> offsets) {
            return Address{Current::EAX, offsets}.Get<T>();
        }

        Address ebx() { return Address{Current::EBX}; }
        Address ebx(uint32_t offset) { return Address{Current::EBX, offset}; }
        Address ebx(std::vector<uint32_t> offsets) { return Address{Current::EBX, offsets}; }
        template <typename T>
        T ebx() {
            return Address{Current::EBX}.Get<T>();
        }
        template <typename T>
        T ebx(uint32_t offset) {
            return Address{Current::EBX, offset}.Get<T>();
        }
        template <typename T>
        T ebx(std::vector<uint32_t> offsets) {
            return Address{Current::EBX, offsets}.Get<T>();
        }

        Address ecx() { return Address{Current::ECX}; }
        Address ecx(uint32_t offset) { return Address{Current::ECX, offset}; }
        Address ecx(std::vector<uint32_t> offsets) { return Address{Current::ECX, offsets}; }
        template <typename T>
        T ecx() {
            return Address{Current::ECX}.Get<T>();
        }
        template <typename T>
        T ecx(uint32_t offset) {
            return Address{Current::ECX, offset}.Get<T>();
        }
        template <typename T>
        T ecx(std::vector<uint32_t> offsets) {
            return Address{Current::ECX, offsets}.Get<T>();
        }

        Address edx() { return Address{Current::EDX}; }
        Address edx(uint32_t offset) { return Address{Current::EDX, offset}; }
        Address edx(std::vector<uint32_t> offsets) { return Address{Current::EDX, offsets}; }
        template <typename T>
        T edx() {
            return Address{Current::EDX}.Get<T>();
        }
        template <typename T>
        T edx(uint32_t offset) {
            return Address{Current::EDX, offset}.Get<T>();
        }
        template <typename T>
        T edx(std::vector<uint32_t> offsets) {
            return Address{Current::EDX, offsets}.Get<T>();
        }

        Address esi() { return Address{Current::ESI}; }
        Address esi(uint32_t offset) { return Address{Current::ESI, offset}; }
        Address esi(std::vector<uint32_t> offsets) { return Address{Current::ESI, offsets}; }
        template <typename T>
        T esi() {
            return Address{Current::ESI}.Get<T>();
        }
        template <typename T>
        T esi(uint32_t offset) {
            return Address{Current::ESI, offset}.Get<T>();
        }
        template <typename T>
        T esi(std::vector<uint32_t> offsets) {
            return Address{Current::ESI, offsets}.Get<T>();
        }

        Address edi() { return Address{Current::EDI}; }
        Address edi(uint32_t offset) { return Address{Current::EDI, offset}; }
        Address edi(std::vector<uint32_t> offsets) { return Address{Current::EDI, offsets}; }
        template <typename T>
        T edi() {
            return Address{Current::EDI}.Get<T>();
        }
        template <typename T>
        T edi(uint32_t offset) {
            return Address{Current::EDI, offset}.Get<T>();
        }
        template <typename T>
        T edi(std::vector<uint32_t> offsets) {
            return Address{Current::EDI, offsets}.Get<T>();
        }

        Address ebp() { return Address{Current::EBP}; }
        Address ebp(uint32_t offset) { return Address{Current::EBP, offset}; }
        Address ebp(std::vector<uint32_t> offsets) { return Address{Current::EBP, offsets}; }
        template <typename T>
        T ebp() {
            return Address{Current::EBP}.Get<T>();
        }
        template <typename T>
        T ebp(uint32_t offset) {
            return Address{Current::EBP, offset}.Get<T>();
        }
        template <typename T>
        T ebp(std::vector<uint32_t> offsets) {
            return Address{Current::EBP, offsets}.Get<T>();
        }

        Address esp() { return Address{Current::ESP}; }
        Address esp(uint32_t offset) { return Address{Current::ESP, offset}; }
        Address esp(std::vector<uint32_t> offsets) { return Address{Current::ESP, offsets}; }
        template <typename T>
        T esp() {
            return Address{Current::ESP}.Get<T>();
        }
        template <typename T>
        T esp(uint32_t offset) {
            return Address{Current::ESP, offset}.Get<T>();
        }
        template <typename T>
        T esp(std::vector<uint32_t> offsets) {
            return Address{Current::ESP, offsets}.Get<T>();
        }
    };
}
