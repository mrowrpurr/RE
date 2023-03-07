#include <Hook.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

// TODO: Uninstall!

void MyDetour() { Output("MyDetour() called!"); }

void SetupHooks() {
    SetModuleName("falloutwHR.exe");
    SetSearchOffset(0x10000);

    RegisterAoB("Drop Item (AoB)", MyDetour, "\x83\xEC\x14\x89\xC1\x89\xD5\x89\x5C\x24\x10");

    RegisterHook(0x46a41c, MyDetour);

    RegisterHook(0x46a41c, [](Registers& regs) {
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
        for (auto& [name, hook] : GetRegisteredHooks()) {
            app.AddButton(string_format("Enable: {}", name), [&]() {
                if (hook->Toggle())
                    app.ChangeButtonText(string_format("Disable: {}", name));
                else
                    app.ChangeButtonText(string_format("Enable: {}", name));
            });
        }
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    SetupHooks();
    RunUI();
    Injected_DLL::EjectDLL();
}
