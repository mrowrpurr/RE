#include <Assembly.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <Memory.h>
#include <UserInterface.h>
#include <string_format.h>

// [x] 1. Read Bytes
// [x] 2. Disassemble Bytes
// [x] 3. Write Bytes
// [ ] 4. Write Bytes from Assembly

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

uintptr_t            address = 0x4ceed9;
size_t               size    = 3;
std::vector<uint8_t> originalBytes;

void ReadMemory() {
    originalBytes = Memory::ReadBytes(address, size);

    std::string bytesString;
    for (auto b : originalBytes) bytesString += string_format("{:02X} ", b);
    Output("Original Bytes: {}", bytesString);

    auto disassembled = Assembly::Disassemble86(originalBytes, address);
    Output("Disassembled: {}", disassembled[0]);
}

void WriteMemory() {
    auto bytes = Assembly::GetBytes([](Assembly::Code code) { code.mov(ptr[ebp - 0x14], ecx); });

    std::string bytesString;
    for (auto b : bytes) bytesString += string_format("{:02X} ", b);
    Output("Bytes from Assembly: {}", bytesString);

    Memory::WriteProtectedBytes(address, bytes);
}

void RestoreMemory() { Memory::WriteProtectedBytes(address, originalBytes); }

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        app.AddButton("Read", [&]() { ReadMemory(); });
        app.AddButton("Write", [&]() { WriteMemory(); });
        app.AddButton("Restore", [&]() { RestoreMemory(); });
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    RunUI();
    Injected_DLL::EjectDLL();
}