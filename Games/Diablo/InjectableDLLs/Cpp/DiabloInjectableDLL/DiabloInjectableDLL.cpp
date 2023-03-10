#include <Injected_DLL.h>
#include <Logging.h>
#include <Memory.h>
#include <UserInterface.h>
#include <string_format.h>

using namespace Memory;

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

uintptr_t address = 0x434b01;
uint32_t  size    = 6;
Bytes     bytes;

void WriteBytes() {
    bytes = MemoryReader{address}.Read(size);
    ProtectedMemoryWriter(address).WriteBytes({0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
}

void ResetBytes() { ProtectedMemoryWriter(address).WriteBytes(bytes); }

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Diablo Trainer")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        app.AddButton("Write Bytes", [&]() { WriteBytes(); });
        app.AddButton("Reset Bytes", [&]() { ResetBytes(); });
        // for (auto hook : GetRegisteredHooks()) {
        //     app.AddButton(string_format("Enable: {}", hook->GetName()), [&, hook]() {
        //         if (hook->Toggle())
        //             app.ChangeButtonText(string_format("Disable: {}", hook->GetName()));
        //         else
        //             app.ChangeButtonText(string_format("Enable: {}", hook->GetName()));
        //     });
        // }
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    // SetupHooks();
    RunUI();
    // UninstallAllHooks();
    Injected_DLL::EjectDLL();
}
