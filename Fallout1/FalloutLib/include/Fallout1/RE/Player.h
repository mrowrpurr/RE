#pragma once

#include <cstdint>

#include "Fallout1/RE/Addresses.h"

namespace Fallout1::RE {

    class Player {
        uintptr_t m_base;

    public:
        Player(uintptr_t base) : m_base(Addresses::PlayerPtr) {}

        // uint32_t GetActionPoints() const { return *reinterpret_cast<uint32_t*>(m_base + 0x3C); }

        // uint32_t GetInventoryCount() const { return *reinterpret_cast<uint32_t*>(m_base + 0x2C); }

        // uint32_t GetInventoryPtr() const { return *reinterpret_cast<uint32_t*>(m_base + 0x30); }

        // uint32_t GetScreenScrollX() const { return *reinterpret_cast<uint32_t*>(m_base + 0x10); }

        // uint32_t GetScreenScrollY() const { return *reinterpret_cast<uint32_t*>(m_base + 0x0C); }

        // uint32_t GetCharacterDirection() const { return *reinterpret_cast<uint32_t*>(m_base + 0x18); }
    };
}