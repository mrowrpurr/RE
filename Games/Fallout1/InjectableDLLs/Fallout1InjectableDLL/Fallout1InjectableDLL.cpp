#include <RE/Helpers/FindByteSignatureAddress.h>
#include <RE/Hooks.h>
#include <RE/InjectedDLL.h>
#include <form_app.h>
#include <string_format.h>

// Hooks.h /////////////////////////////////////////////

////////////////////////////////////////////////////////

#include <functional>
#include <string>
#include <unordered_map>

namespace RE::Hooks {
    struct Hook {
        std::string           name;
        std::function<void()> install;
        std::function<void()> uninstall;
        bool                  enabled = false;
    };

    inline std::unordered_map<std::string, Hook> RegisteredHooks;

    void Add(const std::string& name, std::function<void()> install, std::function<void()> uninstall) {
        RegisteredHooks[name] = {name, install, uninstall};
    }

    void Remove(const std::string& name) { RegisteredHooks.erase(name); }

    bool Toggle(const std::string& name) {
        auto& hook = RegisteredHooks[name];
        if (hook.enabled) {
            hook.uninstall();
            hook.enabled = false;
        } else {
            hook.install();
            hook.enabled = true;
        }
        return hook.enabled;
    }
}

void Hook_CollectEntityList_Detour() {
    //
}

void Hook_CollectEntityList_Install() {
    // auto address = RE::Helpers::FindByteSignatureAddress(
    //     L"falloutwHR.exe", 0x10000,
    //     "\x89\x50\x04\x8B\x06\x89\x58\x28\x8B\x06\xC7\x40\x08\x00\x00\x00\x00\x8B\x06\xC7\x40\x0C\x00\x00\x00\x00",
    //     "xxxxxxxxxxxxxxxxxxxxxxxxxx"
    // );
    // RE::Hooks::Detour32(BYTE *src, BYTE *dst)
    FormApp::App().AppendOutput("This will install the Collect Entity List hook");
}

void Hook_CollectEntityList_Uninstall() {
    FormApp::App().AppendOutput("This will UNINSTALL the Collect Entity List hook");
}

void SetupHooks() {
    RE::Hooks::Add("Collect Entity List", Hook_CollectEntityList_Install, Hook_CollectEntityList_Uninstall);
    RE::Hooks::Add("Another Hook", Hook_CollectEntityList_Install, Hook_CollectEntityList_Uninstall);
}

void RunUI() {
    FormApp::Run([&](FormApp& app) {
        app.SetTitle("Fallout 1 Trainer");
        app.SetButtonHeight(50);
        app.SetHeight(500);
        app.SetWidth(500);
        for (auto& [name, hook] : RE::Hooks::RegisteredHooks) {
            app.AddButton(string_format("Enable: {}", name), [&, name]() {
                if (RE::Hooks::Toggle(name))
                    app.ChangeButtonText(string_format("Disable: {}", name));
                else
                    app.ChangeButtonText(string_format("Enable: {}", name));
            });
        }
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

void OnDllInjection() {
    SetupHooks();
    RunUI();
    RE::InjectedDLL::EjectDLL();
}