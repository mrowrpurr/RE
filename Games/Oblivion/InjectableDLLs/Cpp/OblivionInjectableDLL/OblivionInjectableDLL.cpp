#include <Hook.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

void SetupHooks() {
    RegisterHook<7>("Set X,Y,Z on Entity", 0x4D8A38, [](Registers& regs) {
        auto entityAddress = regs.ecx();
        auto x             = regs.ecx<float>(0x02);
        auto y             = regs.ecx<float>(0x30);
        auto z             = regs.ecx<float>(0x34);
    });
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
