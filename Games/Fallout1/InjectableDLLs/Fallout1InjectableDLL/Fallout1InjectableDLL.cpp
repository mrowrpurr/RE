#include <RE/Helpers/FindByteSignatureAddress.h>
#include <RE/Hooks.h>
#include <RE/InjectedDLL.h>
#include <RE/Util.h>
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

    __asm {
        popad
        mov eax,[esi]
        jmp[Hook_CollectEntityList_Detour_JumpBackAddress]
    }
}
// clang-format on

std::vector<BYTE> bytes;

// \x89\x50\x04\x8B\x06
void Hook_CollectEntityList_Install() {
    if (!Hook_CollectEntityList_Detour_Address)
        Hook_CollectEntityList_Detour_Address = RE::Helpers::FindByteSignatureAddress(
            L"falloutwHR.exe", 0x10000,
            "\x89\x50\x04\x8B\x06\x89\x58\x28\x8B\x06\xC7\x40\x08\x00\x00\x00\x00\x8B\x06\xC7\x40\x0C\x00\x00\x00\x00",
            "xxxxxxxxxxxxxxxxxxxxxxxxxx"
        );

    // Read into the bytes!
    // memcpy_s(originalBytes, 5, (BYTE*)Hook_CollectEntityList_Detour_Address, 5);
    uintptr_t startAddress = Hook_CollectEntityList_Detour_Address;
    for (int i = 0; i < 5; i++) {
        bytes.push_back(*(BYTE*)startAddress);
        startAddress++;
    }

    Hook_CollectEntityList_Detour_JumpBackAddress = Hook_CollectEntityList_Detour_Address + 0x5;
    RE::Hooks::Detour32((BYTE*)Hook_CollectEntityList_Detour_Address, (BYTE*)Hook_CollectEntityList_Detour);
    FormApp::App().AppendOutput(string_format(
        "This will INSTALL the Collect Entity List hook at address: {:x}", Hook_CollectEntityList_Detour_Address
    ));
}

void Hook_CollectEntityList_Uninstall() {
    if (bytes.empty()) {
        FormApp::App().AppendOutput("THE BYTES ARE EMPTY!");
        return;
    }

    // unsigned int length = 5;
    DWORD curProtection;
    // std::vector<BYTE> bytes = {0x89, 0x50, 0x04, 0x8B, 0x06};
    VirtualProtect((BYTE*)Hook_CollectEntityList_Detour_Address, bytes.size(), PAGE_EXECUTE_READWRITE, &curProtection);

    uintptr_t startAddress = Hook_CollectEntityList_Detour_Address;
    for (auto& byte : bytes) {
        *(BYTE*)startAddress = byte;
        startAddress++;
    }

    VirtualProtect((BYTE*)Hook_CollectEntityList_Detour_Address, bytes.size(), curProtection, &curProtection);
    FormApp::App().AppendOutput("Uninstalled the Collect Entity List hook");
}

void SetupHooks() {
    RE::Hooks::Add("Collect Entity List", Hook_CollectEntityList_Install, Hook_CollectEntityList_Uninstall);
}

void RunUI() {
    auto address = RE::Helpers::FindByteSignatureAddress(
        L"falloutwHR.exe", 0x10000,
        "\x89\x50\x04\x8B\x06\x89\x58\x28\x8B\x06\xC7\x40\x08\x00\x00\x00\x00\x8B\x06\xC7\x40\x0C\x00\x00\x00\x00",
        "xxxxxxxxxxxxxxxxxxxxxxxxxx"
    );
    FormApp::Run([&](FormApp& app) {
        app.SetTitle("Fallout 1 Trainer");
        app.SetText(string_format("Address: {:x}", address));
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