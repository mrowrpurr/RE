#include <CodeInjection.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

class MemoryArea {};

using namespace CodeInjection;

void SetupHooks() {
    // Get our stoopid group of bytes which calculates the total!
    auto byteActions = ByteWriterActionGroup{};

    // Add some stoopid bytes!
    byteActions.AddAction<WriteBytesAction>(WriteBytesAction{
        {0x69, 0x69, 0x69, 0x69}
    });

    // Add some which require a relative address to be calculated at write time

    // Get the total!
    Output("Total required bytes: {}", byteActions.GetByteCount());

    // Write some bytes (deferred)

    // Write more bytes (deferred)

    // Get the total count

    // TRAMPOLINE
    // auto trampoline = MemoryArea{};

    // CALL ORIGINAL BYTES

    // STORE THE REGISTERS in GLOBAL VARS

    // PUSH
    // CALL
    // POP

    // RESET REGISTERS

    // JMP to DETOUR+OFFSET (JumpBackAddress)
}

/*
    RegisterHook("Drop Item", 0x46a41c, [](Registers& regs) {
        auto tile = regs.eax(0x4);
        auto pid  = regs.edx(0x64);
        Output("Dropped item: {} on tile: {}", pid, tile);
    });
*/

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
    // UninstallAllHooks();
    Injected_DLL::EjectDLL();
}
