#include <CodeInjection/WithXbyak.h>
#include <Injected_DLL.h>
#include <Memory.h>
#include <UserInterface.h>
#include <StringFormatting.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

CodeInjection::Injection injection{"Gain Health on Hit"};

// ADD LOGGING

void Setup() {
    // VARIABLES
    injection.SetAddress(0x434b01);

    // INSTALL
    injection.BeginInstall();
    injection.SaveBytes<6>("originalBytes");
    injection.WriteAssembly([](Assembly code) { code.mov(eax, 0x696969); });
    injection.EndInstall();

    // UNINSTALL
    injection.BeginUninstall();
    injection.WriteProtectedBytesByVar("originalBytes");
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