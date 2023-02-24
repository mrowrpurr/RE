#pragma once

#include <cstdint>
#include <vector>

#include "Fallout1/RE/ModuleBase.h"

namespace Fallout1::RE {

    // Find Dynamic Memory Allocation Address
    uintptr_t GetAddress(uintptr_t base, const std::vector<uintptr_t>& offsets = {}) {
        uintptr_t address = base;
        for (auto offset : offsets) {
            address = *reinterpret_cast<uintptr_t*>(address) + offset;
        }
        return address;
    }

    template <typename T>
    T GetAddress(uintptr_t base, const std::vector<uintptr_t>& offsets = {}) {
        return reinterpret_cast<T>(GetAddress(base, offsets));
    }

    void SetAddress(uintptr_t base, uintptr_t value) {
        uintptr_t address                      = GetAddress(base);
        *reinterpret_cast<uintptr_t*>(address) = value;
    }

    template <typename T>
    void SetAddress(uintptr_t base, T value) {
        uintptr_t address              = GetAddress(base);
        *reinterpret_cast<T*>(address) = value;
    }
}
