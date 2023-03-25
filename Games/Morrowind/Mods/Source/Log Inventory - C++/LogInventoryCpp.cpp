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

    auto ptr0 = Memory::Read<uintptr_t>(0x400000 + 0x3C67DC);
    Log("ptr0: {}", ptr0);

    auto ptr1 = Memory::Read<uintptr_t>(0x400000 + 0x3C67DC, {0x0, 0x2E8});
    Log("ptr1: {}", ptr1);

    auto ptr2 = Memory::Read<uintptr_t>(0x400000 + 0x3C67DC, {0x0, 0x2E8, 0x4});
    Log("ptr2: {}", ptr2);

    auto ptr3 = Memory::Read<uintptr_t>(0x400000 + 0x3C67DC, {0x0, 0x2E8, 0x4, 0x1c});
    Log("ptr3: {}", ptr3);
    // ^ gives an inventory item.

    auto qty = Memory::Read<uintptr_t>(0x400000 + 0x3C67DC, {0x0, 0x2E8, 0x4, 0x1c, 0xc});
    Log("item qty: {}", qty);

    auto* inventoryItem =
        Memory::Read<InventoryItem*>(0x400000 + 0x3C67DC, {0x0, 0x2E8, 0x4, 0x1c});
    Log("item qty: {}", inventoryItem->qty);
    Log("item name: {}", inventoryItem->name);
}

extern "C" __declspec(dllexport) void Load() {
    Log("Load()");
    PrintOutThePlayerInventory();
}
extern "C" __declspec(dllexport) void Unload() { Log("Unload()"); }
