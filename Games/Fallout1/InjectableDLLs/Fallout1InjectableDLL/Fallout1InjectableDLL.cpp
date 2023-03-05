// #include <RE/Hooks.h>
#include <RE/InjectedDLL.h>
#include <form_app.h>
// #include <logging.h>
// #include <string_format.h>

// void SetupHooks() {}

void RunUI() {
    FormApp::Run([&](FormApp& app) {
        app.SetTitle("Fallout 1 Trainer");
        app.SetButtonHeight(50);
        app.SetHeight(500);
        app.SetWidth(500);
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

void OnDllInjection() {
    // SetupHooks();
    RunUI();
    RE::InjectedDLL::EjectDLL();
}
