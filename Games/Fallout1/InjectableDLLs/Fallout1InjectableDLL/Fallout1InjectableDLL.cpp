#include <CodeInjection/WithXbyak.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <string_format.h>

// TODO - Logger only log IF A LOG NAME IS SET!
// TODO - Set<ProtectedAddress>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

using namespace Memory;
using namespace CodeInjection;

Injection injection{"Pickup double items"};

void SetupHooks() {
    injection.Configure([](Injection& x) {
        x.Set<Address>("address", 0x46A363);
        x.Set<Bytes>("originalBytes");
    });

    injection.OnInstall([](Injection& x) {
        x.ReadBytes("address", "originalBytes", 7);
        x.AllocateMemory("trampoline", [](AllocatedMemory& memory) {
            memory.WriteAssembly([](Assembly code) {
                code.add(ptr[esi + eax + 0x04], edx);
                code.mov(eax, ptr[ecx + 0x08]);
            });
        });
    });

    injection.OnUninstall([](Injection& x) { x.FreeMemory("trampoline"); });
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

// add [esi+eax+04],edx - 01 54 06 04
// mov eax,[ecx+08] - 8B 41 08
// xor edx,edx - 31 D2