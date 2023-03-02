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
        // DWORD                address = 0;
        // std::vector<DWORD>   bytes;
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

//
std::unordered_map<uintptr_t, bool> entityList;
uintptr_t                           entity;
DWORD                               thisEntity = 0x0;
//

DWORD Hook_CollectEntityList_Detour_Address;
DWORD Hook_CollectEntityList_Detour_JumpBackAddress;

// clang-format off
void __declspec(naked) Hook_CollectEntityList_Detour() {
    __asm {
        mov [eax+04],edx
        mov thisEntity,eax
        pushad
    }

    if (thisEntity) {
        entity = thisEntity;
        if (entity) {
            if (!entityList.contains(entity)) {
                entityList[entity] = true;
            }
        }
    }

    // if (thisEntity && !entityList.contains(thisEntity)) entityList[thisEntity] = true;

    __asm {
        popad
        mov eax,[esi]
        jmp[Hook_CollectEntityList_Detour_JumpBackAddress]
    }
}
// clang-format on

void Hook_CollectEntityList_Install() {
    Hook_CollectEntityList_Detour_Address = RE::Helpers::FindByteSignatureAddress(
        L"falloutwHR.exe", 0x10000,
        "\x89\x50\x04\x8B\x06\x89\x58\x28\x8B\x06\xC7\x40\x08\x00\x00\x00\x00\x8B\x06\xC7\x40\x0C\x00\x00\x00\x00",
        "xxxxxxxxxxxxxxxxxxxxxxxxxx"
    );
    Hook_CollectEntityList_Detour_JumpBackAddress = Hook_CollectEntityList_Detour_Address + 0x5;
    RE::Hooks::Detour32((BYTE*)Hook_CollectEntityList_Detour_Address, (BYTE*)Hook_CollectEntityList_Detour);
    FormApp::App().AppendOutput(string_format(
        "This will INSTALL the Collect Entity List hook at address: {:x}", Hook_CollectEntityList_Detour_Address
    ));
}

void Hook_CollectEntityList_Uninstall() {
    // .......
    // DWORD curProtection;
    // VirtualProtect(Hook_CollectEntityList_Detour_Address, 0x5, PAGE_EXECUTE_READWRITE, &curProtection);

    // // ...

    // VirtualProtect(Hook_CollectEntityList_Detour_Address, 0x5, curProtection, &curProtection);

    FormApp::App().AppendOutput("This *will* UNINSTALL the Collect Entity List hook");

    //
    // FormApp::App().AppendOutput("Uninstalled the Collect Entity List hook");
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
        app.AddButton("Print Entity List", [&]() {
            app.AppendOutput(string_format("Entities {}", entityList.size()));
            for (auto& [entity, enabled] : entityList) {
                app.AppendOutput(string_format("Entity: {:x}", entity));
            }
        });
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

void OnDllInjection() {
    SetupHooks();
    RunUI();
    RE::InjectedDLL::EjectDLL();
}