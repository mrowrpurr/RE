#include <Hook.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

// TODO!
bool SomeSignatureThatIFiguredOut(uint8_t, int, const char*) {
    // ....
    // INVOKE_THE_ORIGINAL(0x46a41c, uint8_t, int, const char*)
}

struct FalloutItem {
    uint32_t instanceId;
    uint32_t tileNumber;
};

void SetupHooks() {
    RegisterHook("Drop Item", 0x46a41c, [](Registers& regs) {
        auto tile = regs.eax(0x4);
        auto pid  = regs.edx(0x64);
        Output("Dropped item: {} on tile: {}", pid, tile);
    });

    RegisterHook<7>("Pickup Item (Existing)", 0x46a2ba, [](Registers& regs) {
        auto prototypeId = regs.eax();
        auto itemTile    = regs.edi(0x4);
        Output("Picked up item: {} from tile: {}", prototypeId, itemTile);

        // Get registers from the stack AS A STRUCT*
        auto* item = regs.edi<FalloutItem*>();
        Output("Picked up item {} from tile: {}", item->instanceId, item->tileNumber);

        // Multiple offsets
        auto firstItemPID = regs.ebp({0x34, 0x0, 0x64});
        Output("[MULTIPLE OFFSETS] First Item PID: {}", firstItemPID);
    });
}

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1")
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
