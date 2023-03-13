#include <Injected_DLL.h>
#include <Logging.h>
#include <Mem.h>
#include <UserInterface.h>
#include <string_format.h>

// TODO - Logger only log IF A LOG NAME IS SET!

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

void ReadMemory() {
    auto reader = Mem::MemoryReader(0x4ceed9);
    auto bytes  = reader.Read(3);
    Output("Bytes: {:x} {:X} {:X}", bytes[0], bytes[1], bytes[2]);
}

void DisassembleMemory() {}

void WriteMemory() {
    // TODO - Write memory
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