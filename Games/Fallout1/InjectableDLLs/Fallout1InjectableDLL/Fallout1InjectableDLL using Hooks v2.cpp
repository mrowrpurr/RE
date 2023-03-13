#include <CodeInjection/WithXbyak.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <StringFormatting.h>

// TODO - Logger only log IF A LOG NAME IS SET!
// TODO - Set<ProtectedAddress>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

using namespace Memory;
using namespace CodeInjection;

Injection injection{"Pickup double items"};

void SetupHooks() {
    injection.Configure([](Injection& x) {
        x.Set<Address>("address", 0x46A363);
        x.Set<Address>("jumpBackAddress", 0x46A363 + 7);
        x.Set<Bytes>("originalBytes");
        x.SetBytes("nopBytes", {0x90, 0x90});
        x.Set<Address>("nopAddress", 0x46A363 + 5);
    });

    injection.OnInstall([](Injection& x) {
        x.ReadBytes("address", "originalBytes", 7);
        x.AllocateMemory("trampoline", [](AllocatedMemory& memory) {
            memory.WriteAssembly([](Assembly code) {
                code.add(dword[esi + eax + 0x04], 68);
                code.mov(eax, ptr[ecx + 0x08]);
            });
            memory.WriteJmp("jumpBackAddress");
        });
        x.WriteJmp("address", "trampoline");
        x.WriteBytes("nopAddress", "nopBytes");
    });

    injection.OnUninstall([](Injection& x) {
        x.WriteBytes("address", "originalBytes");
        x.FreeMemory("trampoline");
    });
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

// 09BF0000 - 83 44 30 04 05        - add dword ptr [eax+esi+04],05
