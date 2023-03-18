#include <Assembly.h>
#include <CodeInjection.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <Memory.h>
#include <StringFormatting.h>
#include <UserInterface.h>

#include <cstdint>
#include <string>

SetLogFilePath("InjectedDLL.log");

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

void SetupHooks() {
    CodeInjection::InjectFunction<11>("Drop Item", 0x46a41c, [](Registers& regs) {
        Output("I am a function and I was called!");
        Output("EAX is {:x}", regs.eax());
        Output("EAX 0x0 is {}", regs.eax(0x0));
        Output("EAX 0x34 0x0 is {:x}", regs.eax({0x34, 0x0}));
        Output("EAX 0x34 0x4 is {}", regs.eax({0x34, 0x4}));
        Output("EAX 0x34 0x0 0x64 is {}", regs.eax({0x34, 0x0, 0x64}));
    });

    CodeInjection::New("Freeze Carry Weight")
        .Configure([](Injection& _) {
            _.Var<uintptr_t>("OverwriteAddress", 0x49ceca);
            _.ReadBytes("OverwriteAddress", "OriginalBytes", 3);
        })
        .OnInstall([](Injection& _) { _.WriteNop("OverwriteAddress", 3); })
        .OnUninstall([](Injection& _) { _.WriteBytes("OverwriteAddress", "OriginalBytes"); });
}

void FollowAndLogMysteriousLinkedList() {
    auto startAddress = 0x87E1C98;
    auto nextPointer  = 0x98;
    auto identifier   = 0x0;
    auto tileNumber   = 0x4;
    auto nextAddress  = startAddress;
    while (true) {
        auto next = Memory::Read<uintptr_t>(nextAddress);
        if (next == 0x0) break;
        auto identifierValue = Memory::Read<uint32_t>(next + identifier);
        auto tileNumberValue = Memory::Read<uint32_t>(next + tileNumber);
        Output(
            "Next: {:x} Identifier: {:x} TileNumber: {:x}", next, identifierValue, tileNumberValue
        );
        nextAddress = next + nextPointer;
    }
}

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        for (auto [name, injection] : CodeInjection::RegisteredInjections) {
            app.AddButton(string_format("Enable {}", injection->GetName()), [&, injection]() {
                injection->Toggle();
                if (injection->IsInstalled())
                    app.ChangeButtonText(string_format("Disable {}", injection->GetName()));
                else app.ChangeButtonText(string_format("Enable {}", injection->GetName()));
            });
        }
        app.AddButton("Follow and Log Mysterious Linked List", [&]() {
            FollowAndLogMysteriousLinkedList();
        });
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    SetupHooks();
    RunUI();
    CodeInjection::UninstallAll();
    Injected_DLL::EjectDLL();
}
