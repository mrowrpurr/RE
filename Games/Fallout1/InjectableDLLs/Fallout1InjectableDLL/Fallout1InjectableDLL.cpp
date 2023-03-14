#include <Assembly.h>
#include <CodeInjection.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <Memory.h>
#include <StringFormatting.h>
#include <UserInterface.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

typedef std::vector<uint8_t> Bytes;

std::string PrintBytes(Bytes bytes) {
    std::string result;
    for (auto b : bytes) result += string_format("{:02x} ", b);
    return result;
}

void SetupHooks() {
    CodeInjection::New("Drop Item").Configure([](Injection& _) {
        _.Var("Detour", 0x46a41c);
        _.Var("DetourSize", 5);
        _.Var("JumpBack", _.Var<int>("Detour") + _.Var<int>("DetourSize"));
        _.Var("Trampoline", 0);

        Output("Detour: {:x}", _.Var<int>("Detour"));
        Output("DetourSize: {:x}", _.Var<int>("DetourSize"));
        Output("JumpBack: {:x}", _.Var<int>("JumpBack"));

        _.Var<Bytes>("OriginalBytes", {});
        _.ReadBytes(
            {.addressVariable = "Detour",
             .outVariable     = "OriginalBytes",
             .byteCount       = _.Var<size_t>("DetourSize")}
        );

        auto bytes = _.Var<Bytes>("OriginalBytes");
        Output("OriginalBytes: {}", PrintBytes(bytes));
    });

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