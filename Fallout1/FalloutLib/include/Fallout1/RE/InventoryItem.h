#pragma once

#include <cstdint>

namespace Fallout1::RE {
    struct InventoryItem {
        uintptr_t ptr;
        uint32_t  quantity;
    };
}
