#include <Hook.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

void DropItem_Detour1() {
    // READ THE REGISTERS
    int x = 0x69;
}

void DropItem_Detour2() {
    // READ THE REGISTERS
    int x = 0x420;
}

void SetupHooks() {
    auto& hook = RegisterHook("Drop Item")
                     .SetAddress(0x46a41c)
                     .SetByteCount(11)
                     .SaveRegisters()
                     .CallFunction(DropItem_Detour1)
                     .RestoreRegisters()
                     .CallOriginalBytes()
                     .RestoreRegisters()
                     .CallFunction(DropItem_Detour2)
                     .JumpBack();
}

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        for (auto& [name, hook] : GetRegisteredHooks()) {
            app.AddButton(string_format("Enable: {}", name), [&, name]() {
                if (hook->Toggle())
                    app.ChangeButtonText(string_format("Disable: {}", name));
                else
                    app.ChangeButtonText(string_format("Enable: {}", name));
            });
            // std::string bytesString{};
            // for (auto& byte : hook->GetBytes()) bytesString += string_format("{:02x} ", byte);
            // app.AppendOutput(string_format("Hook: {} Address: {:x} Bytes: {}", name,
            // hook->GetAddress(),
            //                                bytesString));
        }
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    SetupHooks();
    RunUI();
    Injected_DLL::EjectDLL();
}
