#include <Logging.h>
#include <Memory.h>

SetLogFilePath("Modding/Logs/LogInventory.Cpp.log");

struct InventoryItem {
    uint32_t unk0;       // 0x0
    uint32_t unk1;       // 0x4
    uint32_t unk2;       // 0x8
    uint32_t qty;        // 0xc
    uint32_t unk4;       // 0x10
    uint32_t unk5;       // 0x14
    uint32_t unk6;       // 0x18
    char     name[256];  // 0x1c
};

void PrintOutThePlayerInventory() {
    Log("Printing out the player inventory");

    auto inventoryItemsPtr = Memory::Read<uintptr_t>(0x400000 + 0x3C67DC, {0x0, 0x2E8, 0x4});

    uint32_t itemPtrOffset = 0x0;
    while (true) {
        auto value = Memory::Read<uint32_t>(inventoryItemsPtr, itemPtrOffset);
        if (value == 0) break;

        auto* item = Memory::Read<InventoryItem*>(inventoryItemsPtr, itemPtrOffset);
        Log("Item: {}, Qty: {}", item->name, item->qty);

        itemPtrOffset += 0x04;
    }
}

extern "C" __declspec(dllexport) void Load() {
    Log("Load()");
    PrintOutThePlayerInventory();
}
extern "C" __declspec(dllexport) void Unload() { Log("Unload()"); }
