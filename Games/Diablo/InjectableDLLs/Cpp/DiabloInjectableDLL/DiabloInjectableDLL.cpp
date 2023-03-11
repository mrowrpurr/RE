#include <Injected_DLL.h>
#include <Memory.h>
#include <StatefulApp.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

// CodeInjection injection;

StatefulApp::App app;

class WriteBytesAction : public StatefulApp::Action {
    std::vector<uint8_t> _bytes;

public:
    WriteBytesAction(std::vector<uint8_t> bytes) : _bytes(bytes) {}

    void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
        auto address = variables->Get<uintptr_t>("address");
        Memory::MemoryWriter{address}.Protect().WriteBytes(_bytes);
    }
};

void Setup() {
    uintptr_t address       = 0x434b01;
    auto      originalBytes = Memory::MemoryReader{address}.Read(6).GetBytes();

    app.Set<uintptr_t>("address", address);

    app.AddState("Install");
    app.AddAction<WriteBytesAction>(
        "Install", WriteBytesAction({0x90, 0x90, 0x90, 0x90, 0x90, 0x90})
    );

    app.AddState("Uninstall");
    app.AddAction<WriteBytesAction>("Uninstall", WriteBytesAction(originalBytes));
}

void WriteBytes() { app.Goto("Install"); }
void ResetBytes() { app.Goto("Uninstall"); }

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