#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>

void SetupHooks() {}

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1").SetButtonHeight(50).SetHeight(500).SetWidth(500).ShowOutputTextBox();
        //     for (auto& [name, hook] : RE::Hooks::RegisteredHooks) {
        //         app.AddButton(string_format("Enable: {}", name), [&, name]() {
        //             if (hook->Toggle())
        //                 app.ChangeButtonText(string_format("Disable: {}", name));
        //             else
        //                 app.ChangeButtonText(string_format("Enable: {}", name));
        //         });
        //         std::string bytesString{};
        //         for (auto& byte : hook->GetBytes()) bytesString += string_format("{:02x} ", byte);
        //         app.AppendOutput(string_format("Hook: {} Address: {:x} Bytes: {}", name, hook->GetAddress(),
        //         bytesString));
        //     }
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    SetupHooks();
    RunUI();
    Injected_DLL::EjectDLL();
}
