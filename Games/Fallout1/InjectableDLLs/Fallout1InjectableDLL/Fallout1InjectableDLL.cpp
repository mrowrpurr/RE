#include <Assembly.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <Memory.h>
#include <UserInterface.h>
#include <string_format.h>

// [x] 1. Read Bytes
// [x] 2. Disassemble Bytes
// [ ] 3. Write Bytes
// [ ] 4. Write Bytes from Assembly

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

void ReadMemory() {
    auto bytes = Memory::ReadBytes(0x4ceed9, 3);
    Output("Bytes: {:x} {:X} {:X}", bytes[0], bytes[1], bytes[2]);

    auto disassembled = Assembly::Disassemble86(bytes, 0x4ceed9);
    Output("Disassembled: {}", disassembled[0]);
}

void WriteMemory() {
    // TODO - Write memory
}

void WriteAssembly() {
    // TODO - Write assembly
}

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        app.AddButton("Read", [&]() { ReadMemory(); });
        app.AddButton("Write", [&]() { WriteMemory(); });
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    RunUI();
    Injected_DLL::EjectDLL();
}