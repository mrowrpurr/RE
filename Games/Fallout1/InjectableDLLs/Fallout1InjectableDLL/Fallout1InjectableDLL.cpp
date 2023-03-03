#include <RE/Hooks.h>
#include <RE/InjectedDLL.h>
#include <form_app.h>
#include <logging.h>
#include <string_format.h>

void TryToMakeMeALambdaLOL() { FormApp::App().AppendOutput("Hook ran!"); }

void SetupHooks() { RE::Hooks::Add(0x47f6ba, (BYTE*)TryToMakeMeALambdaLOL); }

void RunUI() {
    auto        bytes = RE::Hooks::Get("0x47f6ba").GetBytes();
    std::string bytesString;
    for (auto& byte : bytes) {
        bytesString += string_format("{:02x} ", byte);
    }

    FormApp::Run([&](FormApp& app) {
        app.SetTitle("Fallout 1 Trainer");
        app.SetButtonHeight(50);
        app.SetHeight(500);
        app.SetWidth(500);
        app.SetText(string_format("Bytes: {}", bytesString));
        for (auto& [name, hook] : RE::Hooks::RegisteredHooks) {
            app.AddButton(string_format("Enable: {}", name), [&, name]() {
                if (hook.Toggle())
                    app.ChangeButtonText(string_format("Disable: {}", name));
                else
                    app.ChangeButtonText(string_format("Enable: {}", name));
            });
        }
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

void OnDllInjection() {
    SetupHooks();
    RunUI();
    RE::InjectedDLL::EjectDLL();
}
