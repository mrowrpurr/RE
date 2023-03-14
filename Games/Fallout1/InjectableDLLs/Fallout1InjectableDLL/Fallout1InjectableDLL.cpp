#include <Assembly.h>
#include <CodeInjection.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <Memory.h>
#include <StringFormatting.h>
#include <UserInterface.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

std::string PrintBytes(std::vector<uint8_t> bytes) {
    std::string result;
    for (auto b : bytes) result += string_format("{:02x} ", b);
    return result;
}

void SetupHooks() {
    auto dropItemHook =
        CodeInjection::New("Drop Item")
            .Configure([](Injection& _) {
                _.Var<uintptr_t>("Detour", 0x46a41c);
                _.Var<size_t>("DetourSize", 5);
                _.Var<uintptr_t>(
                    "JumpBack", _.Var<uintptr_t>("Detour") + _.Var<size_t>("DetourSize")
                );
                _.Var<uintptr_t>("Trampoline", 0);
                _.ReadBytes(
                    {.addressVariable = "Detour",
                     .outVariable     = "OriginalBytes",
                     .byteCount       = _.Var<size_t>("DetourSize")}
                );
            })
            .OnInstall([](Injection& _) {
                // _.AllocateMemory({.addressVariable = "Trampoline", .block = [](Injection&) {}});
                _.WriteBytes({
                    .addressVariable = "Detour",
                    .bytes           = {0x69, 0x42, 0x69, 0x42, 0x69},
                });
            })
            .OnUninstall([](Injection& _) {
                _.WriteBytes({
                    .addressVariable = "Detour",
                    .bytesVariable   = "OriginalBytes",
                });
            });
}

void RunUI() {
    auto injections = CodeInjection::RegisteredInjections;

    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        for (auto [name, injection] : injections) {
            app.AddButton(string_format("Enable {}", injection->GetName()), [&, injection]() {
                injection->Toggle();
                if (injection->IsInstalled())
                    app.ChangeButtonText(string_format("Disable {}", injection->GetName()));
                else
                    app.ChangeButtonText(string_format("Enable {}", injection->GetName()));
            });
        }
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    SetupHooks();
    RunUI();
    Injected_DLL::EjectDLL();
}

//     _.WriteAssembly(AssemblyCode {
//         code.mov(eax, ptr[esp + 0x4]);
//         code.nop();
//         code.nop();
//     })