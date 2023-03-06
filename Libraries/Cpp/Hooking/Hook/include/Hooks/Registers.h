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
            trampoline.WriteBytes(Save::EBP);
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
            trampoline.WriteBytes(Restore::EBP);
            trampoline.WriteDword(reinterpret_cast<uint32_t>(&Current::ESP));
        }
    }
}
