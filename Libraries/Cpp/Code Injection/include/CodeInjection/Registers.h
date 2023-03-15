#pragma once

#include <uint128_t.h>

#include <cstdint>

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
