#pragma once

#include <cstdint>
#include <vector>

#include "Fallout1/RE/ModuleBase.h"

namespace Fallout1::RE {

    // Gets the address (with optional offsets) relative to the module base
    uintptr_t GetModuleAddress(uintptr_t base, const std::vector<uintptr_t>& offsets = {}) {
        uintptr_t address = MODULE_BASE + base;
        for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address) + offset;
        return address;
    }

    // Gets the address (with optional offsets) relative to the module base as the specified type
    template <typename T>
    T GetModuleAddress(uintptr_t base, const std::vector<uintptr_t>& offsets = {}) {
        return reinterpret_cast<T>(GetModuleAddress(base, offsets));
    }

    // Sets the address (with optional offsets) relative to the module base to the specified value
    void SetModuleAddress(uintptr_t base, uintptr_t value, const std::vector<uintptr_t>& offsets = {}) {
        uintptr_t address                      = GetModuleAddress(base, offsets);
        *reinterpret_cast<uintptr_t*>(address) = value;
    }

    // Sets the address (with optional offsets) relative to the module base to the specified value as the specified type
    template <typename T>
    void SetModuleAddress(uintptr_t base, T value, const std::vector<uintptr_t>& offsets = {}) {
        uintptr_t address              = GetModuleAddress(base, offsets);
        *reinterpret_cast<T*>(address) = value;
    }

    // Gets the address (with optional offsets) relative to the provided base
    uintptr_t GetAddress(uintptr_t base, const std::vector<uintptr_t>& offsets = {}) {
        uintptr_t address = base;
        for (auto offset : offsets) address = *reinterpret_cast<uintptr_t*>(address) + offset;
        return address;
    }

    // Gets the address (with optional offsets) relative to the provided base as the specified type
    template <typename T>
    T GetAddress(uintptr_t base, const std::vector<uintptr_t>& offsets = {}) {
        return reinterpret_cast<T>(GetAddress(base, offsets));
    }

    // Sets the address (with optional offsets) relative to the provided base to the specified value
    void SetAddress(uintptr_t base, uintptr_t value, const std::vector<uintptr_t>& offsets = {}) {
        uintptr_t address                      = GetAddress(base, offsets);
        *reinterpret_cast<uintptr_t*>(address) = value;
    }

    // Sets the address (with optional offsets) relative to the provided base to the specified value as the specified
    // type
    template <typename T>
    void SetAddress(uintptr_t base, T value, const std::vector<uintptr_t>& offsets = {}) {
        uintptr_t address              = GetAddress(base, offsets);
        *reinterpret_cast<T*>(address) = value;
    }
}
