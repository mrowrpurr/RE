#include <CodeInjection.h>
#include <Injected_DLL.h>
#include <Memory.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

void Setup() {
    CodeInjection::Inject("Gain Health on Hit");

    //.SetAddress(0x434b01);

    // uintptr_t address       = ;
    // auto      originalBytes = Memory::MemoryReader{address}.Read(6).GetBytes();

    // app.Set<uintptr_t>("address", address);

    // app.AddState("Install");
    // app.AddAction<WriteBytesAction>(
    //     "Install", WriteBytesAction({0x90, 0x90, 0x90, 0x90, 0x90, 0x90})
    // );

    // app.AddState("Uninstall");
    // app.AddAction<WriteBytesAction>("Uninstall", WriteBytesAction(originalBytes));
}

void WriteBytes() {
    // app.Goto("Install");
}
void ResetBytes() {
    // app.Goto("Uninstall");
}

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Diablo Trainer")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        app.AddButton("Write Bytes", [&]() { WriteBytes(); });
        app.AddButton("Reset Bytes", [&]() { ResetBytes(); });
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    Setup();
    // SetupHooks();
    RunUI();
    // UninstallAllHooks();
    Injected_DLL::EjectDLL();
}

// bytes = MemoryReader{address}.Read(size);
// ProtectedMemoryWriter(address).WriteBytes({0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
// ProtectedMemoryWriter(address).WriteBytes(bytes);