#pragma once

#include <cstdint>
#include <vector>

#include "Fallout1/RE/ModuleBase.h"

namespace Fallout1::RE {

    // Find Dynamic Memory Allocation Address
    uintptr_t GetAddress(uintptr_t base, const std::vector<uintptr_t>& offsets = {}) {
        uintptr_t address = MODULE_BASE + base;
        for (auto offset : offsets) {
            address = *reinterpret_cast<uintptr_t*>(address) + offset;
        }
        return address;
    }

    template <typename T>
    T* GetAddress(uintptr_t base, const std::vector<uintptr_t>& offsets = {}) {
        return reinterpret_cast<T*>(GetAddress(base, offsets));
    }
}
