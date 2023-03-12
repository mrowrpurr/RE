#include <CodeInjection.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

class MemoryArea {};

using namespace Memory;
using namespace CodeInjection;

// TODO - Logger only log IF A LOG NAME IS SET!

// NEXT: LOGS
// Next Next ALLOC!

Injection injection{"Pickup double items"};

void SetupHooks() {
    injection.Configure([](Injection& x) {
        // Rename to make more clear that it's a VARIABLE?
        x.Set<Address>("address", 0x46a41c);
        x.Set<Bytes>("originalBytes");
        x.SetBytes("newBytes", {0x69, 0x69, 0x69, 0x69});
    });

    injection.OnInstall([](Injection& x) {
        x.ReadBytes("address", "originalBytes", 4);
        x.WriteProtectedBytes("address", "newBytes");
    });

    injection.OnUninstall([](Injection& x) { x.WriteProtectedBytes("address", "originalBytes"); });
}

void Install() { injection.Install(); }
void Uninstall() { injection.Uninstall(); }

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
        app.AddButton("Install", [&]() { Install(); });
        app.AddButton("Uninstall", [&]() { Uninstall(); });
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
