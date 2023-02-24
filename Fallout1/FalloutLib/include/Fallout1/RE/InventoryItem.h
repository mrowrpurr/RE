#pragma once

#include <cstdint>

#include "Fallout1/RE/Item.h"

namespace Fallout1::RE {
    struct InventoryItem {
        Item* item;
        // uint32_t itemPtr;
        uint32_t quantity;
    };
}
