#include <CodeInjection.h>
#include <Injected_DLL.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

// uintptr_t address = 0x434b01;

void Setup() {
    CreateCodeInjection("Diablo Something")
        .On("Load")
        .Do(AllocateMemory(1024))
        .Do(WriteBytes({0x90, 0x90, 0x90, 0x90, 0x90, 0x90}))
        .Do(WriteAsm([](Code& code) { code.move(ptr[esp + 14], eax) }))
        .Do(Call([]() { auto x = EAX(0x4); }));

    CreateCodeInjection("Diablo Something")
        .OnInstall()
        .AllocateMemory(1024)
        .WriteBytes({0x90, 0x90, 0x90, 0x90, 0x90, 0x90})
        .WriteAsm([](Asm& asm) { asm.move(ptr[esp + 14], eax) })
        .Run([]() { auto x = EAX(0x4); });
}

void WriteBytes() {
    //
}

void ResetBytes() {
    //
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

// bytes = MemoryReader{address}.Read(size);
// ProtectedMemoryWriter(address).WriteBytes({0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
// ProtectedMemoryWriter(address).WriteBytes(bytes);