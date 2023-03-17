#include <Assembly.h>
#include <CodeInjection.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <Memory.h>
#include <StringFormatting.h>
#include <UserInterface.h>

#include <cstdint>
#include <string>

SetLogFilePath("InjectedDLL.log");

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

std::string PrintBytes(std::vector<uint8_t> bytes) {
    std::string result;
    for (auto b : bytes) result += string_format("{:02x} ", b);
    return result;
}

// TODO: Overloads

// TODO: Wrappers

void SetupHooks() {
    CodeInjection::New("Drop Item")
        .Configure([](Injection& _) {
            _.Var<uintptr_t>("Detour", 0x46a41c);
            _.Var<size_t>("DetourSize", 5);
            _.Var<uintptr_t>("JumpBack", _.Var<uintptr_t>("Detour") + _.Var<size_t>("DetourSize"));
            _.Var<uintptr_t>("Trampoline", 0);
            _.ReadBytes("Detour", "OriginalBytes", _.Var<size_t>("DetourSize"));
        })
        .OnInstall([](Injection& _) {
            _.AllocateMemory("Trampoline", [](Injection& trampoline) {
                trampoline.SaveGeneralPurposeRegisters();
                trampoline.Call([](Registers& regs) {
                    Output("I am a function and I was called!");
                    Output("EAX is {:x}", regs.eax());
                    Output("EAX 0x0 is {}", regs.eax(0x0));
                    Output("EAX 0x34 0x0 is {:x}", regs.eax({0x34, 0x0}));
                    Output("EAX 0x34 0x4 is {}", regs.eax({0x34, 0x4}));
                    Output("EAX 0x34 0x0 0x64 is {}", regs.eax({0x34, 0x0, 0x64}));
                });
                trampoline.RestoreGeneralPurposeRegisters();
                trampoline.WriteBytes("OriginalBytes");
                trampoline.WriteJmp("JumpBack");
            });
            _.WriteJmp("Detour", "Trampoline");
        })
        .OnUninstall([](Injection& _) {
            _.WriteBytes("Detour", "OriginalBytes");
            _.DeallocateMemory("Trampoline");
        });
}

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1").SetButtonHeight(50).SetHeight(500).SetWidth(500).ShowOutputTextBox();
        for (auto [name, injection] : CodeInjection::RegisteredInjections) {
            app.AddButton(string_format("Enable {}", injection->GetName()), [&, injection]() {
                injection->Toggle();
                if (injection->IsInstalled()) app.ChangeButtonText(string_format("Disable {}", injection->GetName()));
                else app.ChangeButtonText(string_format("Enable {}", injection->GetName()));
            });
        }
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    SetupHooks();
    RunUI();
    CodeInjection::UninstallAll();
    Injected_DLL::EjectDLL();
}
