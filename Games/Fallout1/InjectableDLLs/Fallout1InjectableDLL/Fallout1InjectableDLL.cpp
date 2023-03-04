#include <RE/Hooks.h>
#include <RE/InjectedDLL.h>
#include <form_app.h>
#include <logging.h>
#include <string_format.h>

/*
    # Run Original Bytes First

                [ADDRESS to HOOK]       jmp HOOK_BYTES_LOCATION

                [HOOK_BYTES_LOCATION]   aa bb cc dd ee   <---- Original Bytes
                                        pushad
                                        call <hook function>
                                        popad
                                        jmp <jump back address>

    # Run Original Bytes Last

                [ADDRESS to HOOK]       jmp HOOK_BYTES_LOCATION

                [HOOK_BYTES_LOCATION]   pushad
                                        call jmp <hook function>
                                        popad
                                        aa bb cc dd ee   <---- Original Bytes
                                        jmp <jump back address>

    # Run Original Bytes NEVER

                [ADDRESS to HOOK]       jmp HOOK_BYTES_LOCATION

                [HOOK_BYTES_LOCATION]   pushad
                                        call jmp <hook function>
                                        popad
                                        jmp <jump back address>
*/

int lovely;

void TheHook() {
    lovely = 0x69;
    // FormApp::App().AppendOutput("HAHAHA TheHook() function RAN!");
}

void SetupHooks() {
    // Totally Custom
    // RE::Hooks::Add("Cool Hook", 0x123, installFn, uninstallFn)

    // Detour Function
    // RE::Hooks::Add("Cool Hook", 0x123, detourFnAddress, runOriginalBytes = false)
    // RE::Hooks::Add("Cool Hook", 0x123, detourFnAddress, runOriginalBytesFirst = true)
    // RE::Hooks::Add("Cool Hook", 0x123, detourFnAddress, runOriginalBytesLast = true)

    // Ha, almost lazy-ish function -- IF NAKED, NEED TO ADD A ret
    // RE::Hooks::Add(0x47f6ba, reinterpret_cast<DWORD_PTR>(TheHook));

    // Ha, almost lazy-ish function
    // RE::Hooks::Add(0x47f6ba, reinterpret_cast<DWORD_PTR>(TheHook));

    // RE::Hooks::Add<0x123>([](){
    //     // yummy yummy yum
    // });

    // Haha, lazy f'n lambda!
    RE::Hooks::Add("Update Tile Number", 0x47f6ba, [](auto&) { FormApp::App().AppendOutput("SOMEONE MOVED"); });
    RE::Hooks::Add("Pickup Item", 0x46a2ba, 7, [](RE::Hooks::Registers& regs) {
        FormApp::App().AppendOutput("YOU PICKED UP AN ITEM!");
        auto prototypeId = regs.eax();
        auto item        = regs.edi();  // 0x4 is the tile
        auto player      = regs.ebp();  // 0x4 is the tile
    });

    // MuHaHaHaHa, my Lambda has Registers, byach!!
    // RE::Hooks::Add(0x47f6ba, [](Registers& regs) { FormApp::App().AppendOutput("... {}", regs.eax()); });
}

void RunUI() {
    FormApp::Run([&](FormApp& app) {
        app.SetTitle("Fallout 1 Trainer");
        app.SetButtonHeight(50);
        app.SetHeight(500);
        app.SetWidth(500);
        for (auto& [name, hook] : RE::Hooks::RegisteredHooks) {
            app.AddButton(string_format("Enable: {}", name), [&, name]() {
                if (hook->Toggle())
                    app.ChangeButtonText(string_format("Disable: {}", name));
                else
                    app.ChangeButtonText(string_format("Enable: {}", name));
            });
            std::string bytesString{};
            for (auto& byte : hook->GetBytes()) bytesString += string_format("{:02x} ", byte);
            app.AppendOutput(string_format("Hook: {} Address: {:x} Bytes: {}", name, hook->GetAddress(), bytesString));
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
