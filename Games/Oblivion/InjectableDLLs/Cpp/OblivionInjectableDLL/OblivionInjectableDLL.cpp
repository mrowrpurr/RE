#include <Hook.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <string_format.h>

#include <unordered_set>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

std::unordered_set<uint32_t> discoveredEntities;
std::unordered_set<uint32_t> discoveredEntityInventoryAddresses;

// TODO - cute little helper for following offsets (from uint32_t)
// TODO - ability to write custom detour
// TODO - have the offset helpers return 0 if any of the pointers are nullptr
// TODO - pushad, push, call, pop, popad

int mrowr;

struct NameStruct {
    char name[16];
};

void SetupHooks() {
    RegisterHook<7>("Set X,Y,Z on Entity", 0x4D8A38, [](Registers& regs) {
        if (!discoveredEntities.contains(regs.ecx())) {
            discoveredEntities.insert(regs.ecx());
            Output("Entity: 0x{:x}", regs.ecx());
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
            try {
                if (!regs.eax()) return;

                auto entityInventoryAddress = regs.eax();
                if (!discoveredEntityInventoryAddresses.contains(entityInventoryAddress)) {
                    discoveredEntityInventoryAddresses.insert(entityInventoryAddress);
                    Log("EntityInventoryStruct: 0x{:x}", entityInventoryAddress);
                } else
                    return;

                Log("Trying to read offset 0x0c");
                if (!regs.eax(0x0c)) return;

                Log("Trying to read offsets 0x0c, 0x4");
                if (!regs.eax({0x0c, 0x4})) return;
                Log("Entity address: 0x{:x}", regs.eax({0x0c, 0x4}));

                Log("Trying to read offsets 0x0c, 0x4, 0x1c");
                if (!regs.eax({0x0c, 0x4, 0x1c})) return;

                Log("Trying to read offsets 0x0c, 0x4, 0x1c, 0xa4");
                if (!regs.eax({0x0c, 0x4, 0x1c, 0xa4})) return;

                // Log("Trying to read offsets 0x0c, 0x4, 0x1c, 0xa4, 0x0");
                // if (!regs.eax({0x0c, 0x4, 0x1c, 0xa4, 0x0})) return;

                Log("Ok, we would love to read it now... but how?");
                auto nameStructAddress = regs.eax({0x0c, 0x4, 0x1c, 0xa4});
                Log("NameStruct address: 0x{:x}", nameStructAddress);

                auto* nameStruct = regs.eax<NameStruct*>({0x0c, 0x4, 0x1c, 0xa4});
                Log("NameStruct->name: {}", nameStruct->name);

                Log(".END.");

                // Log("Entity name: {}", regs.eax<const char*>({0x0c, 0x4, 0x1c, 0xa4, 0x0}));
                // auto creatureOrCharacter = regs.eax({0x0c, 0x4});
                // auto inventoryList       = regs.eax({0x0c, 0x0});
                // if (creatureOrCharacter) {
                //     auto name = regs.eax<char*>({0x0c, 0x4, 0x1c, 0xa4, 0x0});
                //     Log("Entity name: {}", name);
                // }
            } catch (std::exception& e) {
                Log("Exception: {}", e.what());
            } catch (...) {
                Log("Unknown exception");
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
