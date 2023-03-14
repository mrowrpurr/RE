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
                _.AllocateMemory({.addressVariable = "Trampoline", .block = [](Injection&) {}});
            })
            .OnUninstall([](Injection&) {
                //
            });

    Output("Detour: {:x}", dropItemHook.Var<uintptr_t>("Detour"));
    Output("DetourSize: {:x}", dropItemHook.Var<size_t>("DetourSize"));
    Output("JumpBack: {:x}", dropItemHook.Var<uintptr_t>("JumpBack"));

    auto bytes = dropItemHook.Var<std::vector<uint8_t>>("OriginalBytes");
    Output("OriginalBytes: {}", PrintBytes(bytes));

    // .OnEnable([](Injection& _) {
    //     _.AllocateMemory({
    //         .addressVariable = "Trampoline",
    //         .code =
    //             [](Injection& trampoline) {
    //                 trampoline.WriteBytes({0x69});
    //                 trampoline.Jmp("JumpBack");
    //             },
    //     });
    //     _.WriteJmp({.addressVariable = "Detour"});
    //     _.WriteNops({.count = 2});
    //     _.WriteAssembly(AssemblyCode {
    //         code.mov(eax, ptr[esp + 0x4]);
    //         code.nop();
    //         code.nop();
    //     })
    // })
    // .OnDisable([](Injection& _) {
    //     _.WriteBytes({.addressVariable = "Detour", .bytesVariable = "OriginalBytes"});
    //     _.DeallocateMemory({.addressVariable = "Trampoline"});
    // });
}

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    SetupHooks();
    RunUI();
    Injected_DLL::EjectDLL();
}