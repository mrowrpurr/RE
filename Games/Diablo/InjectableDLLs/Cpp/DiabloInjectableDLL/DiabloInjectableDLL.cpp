#include <CodeInjection.h>
#include <Injected_DLL.h>
#include <Memory.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

CodeInjection::Injection injection{"Gain Health on Hit"};

void Setup() {
    // VARIABLES
    injection.SetAddress(0x434b01);

    // INSTALL
    injection.BeginInstall();
    injection.SaveBytes<6>("originalBytes");
    injection.WriteProtectedBytes({0x69, 0x42, 0x69, 0x42, 0x69, 0x42});
    // ^--- change to use xbyak
    injection.EndInstall();

    // UNINSTALL
    injection.BeginUninstall();
    injection.WriteProtectedBytes(injection.GetSavedBytes("originalBytes"));
    injection.EndUninstall();
}

void WriteBytes() { injection.Install(); }
void ResetBytes() { injection.Uninstall(); }

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