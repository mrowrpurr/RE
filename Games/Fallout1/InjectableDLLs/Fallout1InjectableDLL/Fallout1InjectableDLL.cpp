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

// TODO: SaveRegisters
// TODO: RestoreRegisters
// TODO: Update Call Lambda to support Registers object reference as a parameter
// TODO: Array of Bytes
// TODO: Write Assembly
// TODO: Add a little Macro for the Write Assembly (just to using namespace Xbyak::util)
// TODO: Overloads
// TODO: Wrappers

void __declspec(naked) I_am_a_function() {
    __asm {
        mov eax, 0x69
        ret
    }
}

void SetupHooks() {
    CodeInjection::New("Drop Item")
        .Configure([](Injection& _) {
            _.Var<uintptr_t>("Detour", 0x46a41c);
            _.Var<size_t>("DetourSize", 5);
            _.Var<uintptr_t>("JumpBack", _.Var<uintptr_t>("Detour") + _.Var<size_t>("DetourSize"));
            _.Var<uintptr_t>("Trampoline", 0);
            _.ReadBytes(
                {.addressVariable = "Detour", .outVariable = "OriginalBytes", .byteCount = _.Var<size_t>("DetourSize")}
            );
        })
        .OnInstall([](Injection& _) {
            _.AllocateMemory({
                .addressVariable = "Trampoline",
                .code =
                    [](Injection& trampoline) {
                        trampoline.WriteNop({.count = 5});
                        // trampoline.SaveRegisters({.registers = {Register::EAX}});
                        trampoline.WriteCall({.toAddress = reinterpret_cast<uintptr_t>(&I_am_a_function)});
                        trampoline.WriteNop({.count = 5});
                        trampoline.Call({.function = []() { Output("I am a function and I was called!"); }});
                        trampoline.WriteNop({.count = 5});
                        trampoline.WriteBytes({.bytesVariable = "OriginalBytes"});
                        trampoline.WriteNop({.count = 5});
                        trampoline.WriteJmp({.toAddressVariable = "JumpBack"});
                    },
            });
            _.WriteJmp({
                .fromAddressVariable = "Detour",
                .toAddressVariable   = "Trampoline",
            });
        })
        .OnUninstall([](Injection& _) {
            _.WriteBytes({
                .addressVariable = "Detour",
                .bytesVariable   = "OriginalBytes",
            });
            _.DeallocateMemory({.addressVariable = "Trampoline"});
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
    // CodeInjection::UninstallAll();
    Injected_DLL::EjectDLL();
}
