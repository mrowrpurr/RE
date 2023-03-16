#pragma once

#include <uint128_t.h>

#include <cstdint>
#include <unordered_map>

namespace CodeInjection {

    enum class Register {
        EAX,
        EBX,
        ECX,
        EDX,
        ESI,
        EDI,
        ESP,
        EBP,
        RAX,
        RBX,
        RCX,
        RDX,
        RSI,
        RDI,
        RSP,
        RBP,
        R8,
        R9,
        R10,
        R11,
        R12,
        R13,
        R14,
        R15,
        // R8D,
        // R9D,
        // R10D,
        // R11D,
        // R12D,
        // R13D,
        // R14D,
        // R15D,
        // R8W,
        // R9W,
        // R10W,
        // R11W,
        // R12W,
        // R13W,
        // R14W,
        // R15W,
        // R8B,
        // R9B,
        // R10B,
        // R11B,
        // R12B,
        // R13B,
        // R14B,
        // R15B,
        XMM0,
        XMM1,
        XMM2,
        XMM3,
        XMM4,
        XMM5,
        XMM6,
        XMM7,
        XMM8,
        XMM9,
        XMM10,
        XMM11,
        XMM12,
        XMM13,
        XMM14,
        XMM15,
        XMM16,
        XMM17,
        XMM18,
        XMM19,
        XMM20,
        XMM21,
        XMM22,
        XMM23,
        XMM24,
        XMM25,
        XMM26,
        XMM27,
        XMM28,
        XMM29,
        XMM30,
        XMM31,
        // YMM0,
        // YMM1,
        // YMM2,
        // YMM3,
        // YMM4,
        // YMM5,
        // YMM6,
        // YMM7,
        // YMM8,
        // YMM9,
        // YMM10,
        // YMM11,
        // YMM12,
        // YMM13,
        // YMM14,
        // YMM15,
        // YMM16,
        // YMM17,
        // YMM18,
        // YMM19,
        // YMM20,
        // YMM21,
        // YMM22,
        // YMM23,
        // YMM24
    };

    namespace Registers {

        namespace CurrentValues {
            uint32_t EAX = 0;
            uint32_t EBX = 0;
            uint32_t ECX = 0;
            uint32_t EDX = 0;
            uint32_t ESI = 0;
            uint32_t EDI = 0;
            uint32_t ESP = 0;
            uint32_t EBP = 0;
            uint64_t RAX = 0;
            uint64_t RBX = 0;
            uint64_t RCX = 0;
            uint64_t RDX = 0;
            uint64_t RSI = 0;
            uint64_t RDI = 0;
            uint64_t RSP = 0;
            uint64_t RBP = 0;
            uint64_t R8  = 0;
            uint64_t R9  = 0;
            uint64_t R10 = 0;
            uint64_t R11 = 0;
            uint64_t R12 = 0;
            uint64_t R13 = 0;
            uint64_t R14 = 0;
            uint64_t R15 = 0;
            // uint32_t  R8D   = 0;
            // uint32_t  R9D   = 0;
            // uint32_t  R10D  = 0;
            // uint32_t  R11D  = 0;
            // uint32_t  R12D  = 0;
            // uint32_t  R13D  = 0;
            // uint32_t  R14D  = 0;
            // uint32_t  R15D  = 0;
            // uint16_t  R8W   = 0;
            // uint16_t  R9W   = 0;
            // uint16_t  R10W  = 0;
            // uint16_t  R11W  = 0;
            // uint16_t  R12W  = 0;
            // uint16_t  R13W  = 0;
            // uint16_t  R14W  = 0;
            // uint16_t  R15W  = 0;
            // uint8_t   R8B   = 0;
            // uint8_t   R9B   = 0;
            // uint8_t   R10B  = 0;
            // uint8_t   R11B  = 0;
            // uint8_t   R12B  = 0;
            // uint8_t   R13B  = 0;
            // uint8_t   R14B  = 0;
            // uint8_t   R15B  = 0;
            uint128_t XMM0  = 0;
            uint128_t XMM1  = 0;
            uint128_t XMM2  = 0;
            uint128_t XMM3  = 0;
            uint128_t XMM4  = 0;
            uint128_t XMM5  = 0;
            uint128_t XMM6  = 0;
            uint128_t XMM7  = 0;
            uint128_t XMM8  = 0;
            uint128_t XMM9  = 0;
            uint128_t XMM10 = 0;
            uint128_t XMM11 = 0;
            uint128_t XMM12 = 0;
            uint128_t XMM13 = 0;
            uint128_t XMM14 = 0;
            uint128_t XMM15 = 0;
            uint128_t XMM16 = 0;
            uint128_t XMM17 = 0;
            uint128_t XMM18 = 0;
            uint128_t XMM19 = 0;
            uint128_t XMM20 = 0;
            uint128_t XMM21 = 0;
            uint128_t XMM22 = 0;
            uint128_t XMM23 = 0;
            uint128_t XMM24 = 0;
            uint128_t XMM25 = 0;
            uint128_t XMM26 = 0;
            uint128_t XMM27 = 0;
            uint128_t XMM28 = 0;
            uint128_t XMM29 = 0;
            uint128_t XMM30 = 0;
            uint128_t XMM31 = 0;
            // uint256_t YMM0  = 0;
            // uint256_t YMM1  = 0;
            // uint256_t YMM2  = 0;
            // uint256_t YMM3  = 0;
            // uint256_t YMM4  = 0;
            // uint256_t YMM5  = 0;
            // uint256_t YMM6  = 0;
            // uint256_t YMM7  = 0;
            // uint256_t YMM8  = 0;
            // uint256_t YMM9  = 0;
            // uint256_t YMM10 = 0;
            // uint256_t YMM11 = 0;
            // uint256_t YMM12 = 0;
            // uint256_t YMM13 = 0;
            // uint256_t YMM14 = 0;
            // uint256_t YMM15 = 0;
            // uint256_t YMM16 = 0;
            // uint256_t YMM17 = 0;
            // uint256_t YMM18 = 0;
            // uint256_t YMM19 = 0;
            // uint256_t YMM20 = 0;
            // uint256_t YMM21 = 0;
            // uint256_t YMM22 = 0;
            // uint256_t YMM23 = 0;
            // uint256_t YMM24 = 0;
        }

        class RegistersReader {
        public:
            uint32_t eax() { return CurrentValues::EAX; }
            template <typename T>
            T eax(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::EAX + offset);
                return (T)(address);
            }
            template <typename T>
            T eax(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::EAX;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint32_t eax(uint32_t offset) { return eax<uint32_t>(offset); }
            uint32_t eax(std::vector<uint32_t> offsets) { return eax<uint32_t>(offsets); }

            uint32_t ebx() { return CurrentValues::EBX; }
            template <typename T>
            T ebx(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::EBX + offset);
                return (T)(address);
            }
            template <typename T>
            T ebx(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::EBX;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint32_t ebx(uint32_t offset) { return ebx<uint32_t>(offset); }
            uint32_t ebx(std::vector<uint32_t> offsets) { return ebx<uint32_t>(offsets); }

            uint32_t ecx() { return CurrentValues::ECX; }
            template <typename T>
            T ecx(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::ECX + offset);
                return (T)(address);
            }
            template <typename T>
            T ecx(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::ECX;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint32_t ecx(uint32_t offset) { return ecx<uint32_t>(offset); }
            uint32_t ecx(std::vector<uint32_t> offsets) { return ecx<uint32_t>(offsets); }

            uint32_t edx() { return CurrentValues::EDX; }
            template <typename T>
            T edx(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::EDX + offset);
                return (T)(address);
            }
            template <typename T>
            T edx(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::EDX;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint32_t edx(uint32_t offset) { return edx<uint32_t>(offset); }
            uint32_t edx(std::vector<uint32_t> offsets) { return edx<uint32_t>(offsets); }

            uint32_t esi() { return CurrentValues::ESI; }
            template <typename T>
            T esi(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::ESI + offset);
                return (T)(address);
            }
            template <typename T>
            T esi(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::ESI;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint32_t esi(uint32_t offset) { return esi<uint32_t>(offset); }
            uint32_t esi(std::vector<uint32_t> offsets) { return esi<uint32_t>(offsets); }

            uint32_t edi() { return CurrentValues::EDI; }
            template <typename T>
            T edi(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::EDI + offset);
                return (T)(address);
            }
            template <typename T>
            T edi(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::EDI;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint32_t edi(uint32_t offset) { return edi<uint32_t>(offset); }
            uint32_t edi(std::vector<uint32_t> offsets) { return edi<uint32_t>(offsets); }

            uint32_t ebp() { return CurrentValues::EBP; }
            template <typename T>
            T ebp(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::EBP + offset);
                return (T)(address);
            }
            template <typename T>
            T ebp(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::EBP;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint32_t ebp(uint32_t offset) { return ebp<uint32_t>(offset); }
            uint32_t ebp(std::vector<uint32_t> offsets) { return ebp<uint32_t>(offsets); }

            uint32_t esp() { return CurrentValues::ESP; }
            template <typename T>
            T esp(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::ESP + offset);
                return (T)(address);
            }
            template <typename T>
            T esp(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::ESP;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint32_t esp(uint32_t offset) { return esp<uint32_t>(offset); }
            uint32_t esp(std::vector<uint32_t> offsets) { return esp<uint32_t>(offsets); }

            uint64_t rax() { return CurrentValues::RAX; }
            template <typename T>
            T rax(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::RAX + offset);
                return (T)(address);
            }
            template <typename T>
            T rax(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::RAX;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint64_t rax(uint32_t offset) { return rax<uint64_t>(offset); }
            uint64_t rax(std::vector<uint32_t> offsets) { return rax<uint64_t>(offsets); }

            uint64_t rbx() { return CurrentValues::RBX; }
            template <typename T>
            T rbx(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::RBX + offset);
                return (T)(address);
            }
            template <typename T>
            T rbx(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::RBX;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint64_t rbx(uint32_t offset) { return rbx<uint64_t>(offset); }
            uint64_t rbx(std::vector<uint32_t> offsets) { return rbx<uint64_t>(offsets); }

            uint64_t rcx() { return CurrentValues::RCX; }
            template <typename T>
            T rcx(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::RCX + offset);
                return (T)(address);
            }
            template <typename T>
            T rcx(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::RCX;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint64_t rcx(uint32_t offset) { return rcx<uint64_t>(offset); }
            uint64_t rcx(std::vector<uint32_t> offsets) { return rcx<uint64_t>(offsets); }

            uint64_t rdx() { return CurrentValues::RDX; }
            template <typename T>
            T rdx(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::RDX + offset);
                return (T)(address);
            }
            template <typename T>
            T rdx(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::RDX;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint64_t rdx(uint32_t offset) { return rdx<uint64_t>(offset); }
            uint64_t rdx(std::vector<uint32_t> offsets) { return rdx<uint64_t>(offsets); }

            uint64_t rsi() { return CurrentValues::RSI; }
            template <typename T>
            T rsi(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::RSI + offset);
                return (T)(address);
            }
            template <typename T>
            T rsi(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::RSI;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint64_t rsi(uint32_t offset) { return rsi<uint64_t>(offset); }
            uint64_t rsi(std::vector<uint32_t> offsets) { return rsi<uint64_t>(offsets); }

            uint64_t rdi() { return CurrentValues::RDI; }
            template <typename T>
            T rdi(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::RDI + offset);
                return (T)(address);
            }
            template <typename T>
            T rdi(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::RDI;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint64_t rdi(uint32_t offset) { return rdi<uint64_t>(offset); }
            uint64_t rdi(std::vector<uint32_t> offsets) { return rdi<uint64_t>(offsets); }

            uint64_t rbp() { return CurrentValues::RBP; }
            template <typename T>
            T rbp(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::RBP + offset);
                return (T)(address);
            }
            template <typename T>
            T rbp(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::RBP;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint64_t rbp(uint32_t offset) { return rbp<uint64_t>(offset); }
            uint64_t rbp(std::vector<uint32_t> offsets) { return rbp<uint64_t>(offsets); }

            uint64_t rsp() { return CurrentValues::RSP; }
            template <typename T>
            T rsp(uint32_t offset) {
                auto address = *reinterpret_cast<uintptr_t*>(CurrentValues::RSP + offset);
                return (T)(address);
            }
            template <typename T>
            T rsp(std::vector<uint32_t> offsets) {
                auto address = CurrentValues::RSP;
                for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address + offset);
                return (T)(address);
            }
            uint64_t rsp(uint32_t offset) { return rsp<uint64_t>(offset); }
            uint64_t rsp(std::vector<uint32_t> offsets) { return rsp<uint64_t>(offsets); }

            // TODO : Add more registers
        };

        namespace Instructions {
            namespace Store {
                std::vector<uint8_t> EAX   = {0xA3};
                std::vector<uint8_t> EBX   = {0x89, 0x1D};
                std::vector<uint8_t> ECX   = {0x89, 0x0D};
                std::vector<uint8_t> EDX   = {0x89, 0x15};
                std::vector<uint8_t> ESI   = {0x89, 0x35};
                std::vector<uint8_t> EDI   = {0x89, 0x3D};
                std::vector<uint8_t> EBP   = {0x89, 0x2D};
                std::vector<uint8_t> ESP   = {0x89, 0x25};
                std::vector<uint8_t> RAX   = {0x48, 0xA3};
                std::vector<uint8_t> RBX   = {0x48, 0x89, 0x1D};
                std::vector<uint8_t> RCX   = {0x48, 0x89, 0x0D};
                std::vector<uint8_t> RDX   = {0x48, 0x89, 0x15};
                std::vector<uint8_t> RSI   = {0x48, 0x89, 0x35};
                std::vector<uint8_t> RDI   = {0x48, 0x89, 0x3D};
                std::vector<uint8_t> RBP   = {0x48, 0x89, 0x2D};
                std::vector<uint8_t> RSP   = {0x48, 0x89, 0x25};
                std::vector<uint8_t> R8    = {0x4C, 0x89, 0x05};
                std::vector<uint8_t> R9    = {0x4C, 0x89, 0x0D};
                std::vector<uint8_t> R10   = {0x4C, 0x89, 0x15};
                std::vector<uint8_t> R11   = {0x4C, 0x89, 0x1D};
                std::vector<uint8_t> R12   = {0x4C, 0x89, 0x25};
                std::vector<uint8_t> R13   = {0x4C, 0x89, 0x2D};
                std::vector<uint8_t> R14   = {0x4C, 0x89, 0x35};
                std::vector<uint8_t> R15   = {0x4C, 0x89, 0x3D};
                std::vector<uint8_t> XMM0  = {0x0F, 0x11, 0x05};
                std::vector<uint8_t> XMM1  = {0x0F, 0x11, 0x0D};
                std::vector<uint8_t> XMM2  = {0x0F, 0x11, 0x15};
                std::vector<uint8_t> XMM3  = {0x0F, 0x11, 0x1D};
                std::vector<uint8_t> XMM4  = {0x0F, 0x11, 0x25};
                std::vector<uint8_t> XMM5  = {0x0F, 0x11, 0x2D};
                std::vector<uint8_t> XMM6  = {0x0F, 0x11, 0x35};
                std::vector<uint8_t> XMM7  = {0x0F, 0x11, 0x3D};
                std::vector<uint8_t> XMM8  = {0x0F, 0x11, 0x45};
                std::vector<uint8_t> XMM9  = {0x0F, 0x11, 0x4D};
                std::vector<uint8_t> XMM10 = {0x0F, 0x11, 0x55};
                std::vector<uint8_t> XMM11 = {0x0F, 0x11, 0x5D};
                std::vector<uint8_t> XMM12 = {0x0F, 0x11, 0x65};
                std::vector<uint8_t> XMM13 = {0x0F, 0x11, 0x6D};
                std::vector<uint8_t> XMM14 = {0x0F, 0x11, 0x75};
                std::vector<uint8_t> XMM15 = {0x0F, 0x11, 0x7D};
            }

            namespace Restore {
                std::vector<uint8_t> EAX   = {0x8B, 0x05};
                std::vector<uint8_t> EBX   = {0x8B, 0x1D};
                std::vector<uint8_t> ECX   = {0x8B, 0x0D};
                std::vector<uint8_t> EDX   = {0x8B, 0x15};
                std::vector<uint8_t> ESI   = {0x8B, 0x35};
                std::vector<uint8_t> EDI   = {0x8B, 0x3D};
                std::vector<uint8_t> EBP   = {0x8B, 0x2D};
                std::vector<uint8_t> ESP   = {0x8B, 0x25};
                std::vector<uint8_t> RAX   = {0x48, 0x8B, 0x05};
                std::vector<uint8_t> RBX   = {0x48, 0x8B, 0x1D};
                std::vector<uint8_t> RCX   = {0x48, 0x8B, 0x0D};
                std::vector<uint8_t> RDX   = {0x48, 0x8B, 0x15};
                std::vector<uint8_t> RSI   = {0x48, 0x8B, 0x35};
                std::vector<uint8_t> RDI   = {0x48, 0x8B, 0x3D};
                std::vector<uint8_t> RBP   = {0x48, 0x8B, 0x2D};
                std::vector<uint8_t> RSP   = {0x48, 0x8B, 0x25};
                std::vector<uint8_t> R8    = {0x4C, 0x8B, 0x05};
                std::vector<uint8_t> R9    = {0x4C, 0x8B, 0x0D};
                std::vector<uint8_t> R10   = {0x4C, 0x8B, 0x15};
                std::vector<uint8_t> R11   = {0x4C, 0x8B, 0x1D};
                std::vector<uint8_t> R12   = {0x4C, 0x8B, 0x25};
                std::vector<uint8_t> R13   = {0x4C, 0x8B, 0x2D};
                std::vector<uint8_t> R14   = {0x4C, 0x8B, 0x35};
                std::vector<uint8_t> R15   = {0x4C, 0x8B, 0x3D};
                std::vector<uint8_t> XMM0  = {0x0F, 0x10, 0x05};
                std::vector<uint8_t> XMM1  = {0x0F, 0x10, 0x0D};
                std::vector<uint8_t> XMM2  = {0x0F, 0x10, 0x15};
                std::vector<uint8_t> XMM3  = {0x0F, 0x10, 0x1D};
                std::vector<uint8_t> XMM4  = {0x0F, 0x10, 0x25};
                std::vector<uint8_t> XMM5  = {0x0F, 0x10, 0x2D};
                std::vector<uint8_t> XMM6  = {0x0F, 0x10, 0x35};
                std::vector<uint8_t> XMM7  = {0x0F, 0x10, 0x3D};
                std::vector<uint8_t> XMM8  = {0x0F, 0x10, 0x45};
                std::vector<uint8_t> XMM9  = {0x0F, 0x10, 0x4D};
                std::vector<uint8_t> XMM10 = {0x0F, 0x10, 0x55};
                std::vector<uint8_t> XMM11 = {0x0F, 0x10, 0x5D};
                std::vector<uint8_t> XMM12 = {0x0F, 0x10, 0x65};
                std::vector<uint8_t> XMM13 = {0x0F, 0x10, 0x6D};
                std::vector<uint8_t> XMM14 = {0x0F, 0x10, 0x75};
                std::vector<uint8_t> XMM15 = {0x0F, 0x10, 0x7D};
            }
        }
    }
}
