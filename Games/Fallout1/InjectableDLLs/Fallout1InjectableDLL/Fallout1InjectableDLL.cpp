#include <Assembly.h>
#include <CodeInjection.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <Memory.h>
#include <StringFormatting.h>
#include <UserInterface.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

void SetupHooks() {
    CodeInjection::New("Drop Item")
        .Configure([](Injection& _) {
            _.AddressVariable("Detour", 0x46a41c);
            _.SizeVariable("DetourSize", 7);
            _.AddressVariable("JumpBack", _.AddressVariable("Detour") +
            _.SizeVariable("DetourSize");
            _.AddressVariable("Trampoline", 0);
            _.BytesVariable("OriginalBytes", {});
            _.ReadBytes(
                {.outVariable = "Detour", .addressVariable = "OriginalBytes", .byteCount = 5}
            );
        })
        .OnEnable([](Injection& _) {
            _.AllocateMemory({
                .addressVariable = "Trampoline",
                .code =
                    [](Injection& trampoline) {
                        trampoline.WriteBytes({0x69});
                        trampoline.Jmp("JumpBack");
                    },
            });
            _.WriteJmp({.addressVariable = "Detour"});
            _.WriteNops({.count = 2});
            _.WriteAssembly(AssemblyCode {
                _.nop();
                _.nop();
            })
        })
        .OnDisable([](Injection& _) {
            _.WriteBytes({.addressVariable = "Detour", .bytesVariable = "OriginalBytes"});
            _.DeallocateMemory({.addressVariable = "Trampoline"});
        });
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