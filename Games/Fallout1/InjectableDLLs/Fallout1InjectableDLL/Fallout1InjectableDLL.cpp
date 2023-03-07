#include <Hook.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

void SetupHooks() {
    RegisterHook("Drop Item", 0x46a41c, [](Registers& regs) {
        auto tile = regs.eax<int>(0x4);
        auto pid  = regs.edx<int>(0x64);
        Output("Dropped item: {} on tile: {}", pid, tile);
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
