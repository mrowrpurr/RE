#include <Hook.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <string_format.h>

#include <unordered_set>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

std::unordered_set<uint32_t> discoveredEntities;
std::unordered_set<uint32_t> discoveredEntityInventoryAddresses;

// TODO - ability to write custom detour
// TODO - pushad, push, call, pop, popad
// TODO - try T with inline structs

struct ItemName {
    char name[255];
};

struct TESForm {
    uint32_t  vtable;
    uint32_t  unk04;
    uint32_t  unk08;
    uint32_t  formId;
    uint32_t  unk10;
    uint32_t  unk14;
    uint32_t  unk18;
    uint32_t  unk1C;
    uint32_t  unk20;
    uint32_t  unk24;
    ItemName* itemName;
};

struct ItemInventoryInfo {
    uint32_t unkItemPtr;
    uint32_t quantity;
    TESForm* itemForm;
};

struct InventoryItemAndNext {
    ItemInventoryInfo*    itemInventoryInfo;
    InventoryItemAndNext* next;
};

void SetupHooks() {
    RegisterHook<7>("Set X,Y,Z on Entity", 0x4D8A38, [](Registers& regs) {
        if (!discoveredEntities.contains(regs.ecx())) {
            discoveredEntities.insert(regs.ecx());
            Output("Entity: 0x{:x}", regs.ecx<int>());
        }
    });

    RegisterHook<10>("Entity + Inventory", 0x41e6f9)
        .OnInstall([](Hook& hook) {
            hook.BackupOriginalDetourBytes();
            hook.WriteTrampoline();
            hook.GetDetour().WriteProtectedBytes({0x74, 0x05});
            hook.GetDetour().WriteProtectedJmp(hook.GetTrampoline().GetAddress());
            hook.GetDetour().WriteProtectedBytes({0x33, 0xC0, 0xC3});
        })
        .SaveRegisters()
        .Call([](Registers& regs) {
            auto entityInventoryAddress = regs.eax();
            if (!discoveredEntityInventoryAddresses.contains(entityInventoryAddress)) {
                discoveredEntityInventoryAddresses.insert(entityInventoryAddress);
                Log("EntityInventoryStruct: 0x{:x}", entityInventoryAddress.Get<int>());
            } else
                return;

            auto objectAndInventory = regs.eax(0x0c);
            auto object             = objectAndInventory(0x4);
            auto formID             = object(0xc).As<int>();
            auto baseObject         = object(0x1c);
            auto baseFormID         = baseObject(0xc).As<int>();
            auto baseName           = baseObject.GetArray<char>({0xa4, 0x0}).data();
            Output(
                "FormID: 0x{:x}, BaseFormID: 0x{:x}, BaseName: {}", formID, baseFormID, baseName
            );

            auto inventory = objectAndInventory(0x0).As<InventoryItemAndNext*>();
            while (inventory->next) {
                auto itemInventoryInfo = inventory->itemInventoryInfo;
                auto itemForm          = itemInventoryInfo->itemForm;
                auto itemName          = itemForm->itemName->name;
                auto itemQuantity      = itemInventoryInfo->quantity;
                Output("Item: {} ({}), Quantity: {}", itemName, itemForm->formId, itemQuantity);
                inventory = inventory->next;
            }
        })
        .RestoreRegisters()
        .WriteBytes({0x8B, 0x40, 0x0C, 0xC3});
}

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Oblivion Trainer")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        for (auto hook : GetRegisteredHooks()) {
            app.AddButton(string_format("Enable: {}", hook->GetName()), [&, hook]() {
                if (hook->Toggle())
                    app.ChangeButtonText(string_format("Disable: {}", hook->GetName()));
                else
                    app.ChangeButtonText(string_format("Enable: {}", hook->GetName()));
            });
        }
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    SetupHooks();
    RunUI();
    UninstallAllHooks();
    Injected_DLL::EjectDLL();
}
