#include <DatFile.h>
#include <DatFileItem.h>

using namespace DatUnpacker;

DatFile* datFile = nullptr;

void ToLower(std::string& str) {
    for (auto& c : str) c = tolower(c);
}

std::string GetNameOfItem(unsigned int prototypeId) {
    auto items = datFile->items();
    if (items == nullptr) return "Items was nullptr";
    for (auto* item : *items) {
        auto name = item->name();
        ToLower(name);
        if (name.ends_with("pro_item.msg") && name.contains("english")) {
            auto* text             = item->data();
            auto  lineNumber       = 0;
            auto  targetLineNumber = prototypeId * 2 - 2;
            for (auto* line = text; *line != '\0'; ++line) {
                if (*line == '\n') {
                    ++lineNumber;
                    if (lineNumber == targetLineNumber) {
                        auto* nameStart = line + 1;
                        auto* nameEnd   = nameStart;
                        while (*nameEnd != '\n') ++nameEnd;
                        return std::string{nameStart, nameEnd};
                    }
                }
            }
        }
    }
    return "Unknown";
}

void ReadPlayerInventory() {
    auto moduleBase         = 0x400000;  // Hardcoded for now
    auto staticCharacterPtr = moduleBase + 0x262844;

    auto playerInventoryPtr = Memory::Read<uint32_t>(staticCharacterPtr, {0x0, 0x34});

    uintptr_t itemPtr  = 0;
    size_t    quantity = 0;

    while (itemPtr != 0xCCCCCCCC) {
        itemPtr  = Memory::Read<uintptr_t>(playerInventoryPtr, 0x0);
        quantity = Memory::Read<uint32_t>(playerInventoryPtr, 0x4);
        playerInventoryPtr += 0x8;
        if (itemPtr == 0xCCCCCCCC) break;

        auto itemPID  = Memory::Read<uint32_t>(itemPtr, 0x64);
        auto itemName = GetNameOfItem(itemPID);
        Output("The player has {} items of item {} (ID {})\n", quantity, itemName, itemPID);
    }
}
datFile = new DatFile{"D:\\GOG\\Games\\Fallout\\MASTER.DAT"};
datFile->version();  // LOL