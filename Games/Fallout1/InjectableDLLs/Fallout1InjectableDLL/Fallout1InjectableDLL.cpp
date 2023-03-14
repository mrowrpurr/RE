#include <Assembly.h>
// #include <CodeInjection.h>
#include <DatFile.h>
#include <DatFileItem.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <Memory.h>
#include <StringFormatting.h>
#include <UserInterface.h>

#include <cstdint>
#include <string>

using namespace DatUnpacker;

void ToLower(std::string& str) {
    for (auto& c : str) c = tolower(c);
}

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

std::string PrintBytes(std::vector<uint8_t> bytes) {
    std::string result;
    for (auto b : bytes) result += string_format("{:02x} ", b);
    return result;
}

DatFile* datFile = nullptr;

std::string GetNameOfItem(unsigned int prototypeId) {
    auto items = datFile->items();
    if (items == nullptr) return "Items was nullptr";
    for (auto* item : *items) {
        auto name = item->name();
        ToLower(name);
        if (name.ends_with("pro_item.msg") && name.contains("english")) {
            auto* text             = item->data();
            auto  lineNumber       = 0;
            auto  targetLineNumber = prototypeId * 2 - 2;
            for (auto* line = text; *line != '\0'; ++line) {
                if (*line == '\n') {
                    ++lineNumber;
                    if (lineNumber == targetLineNumber) {
                        auto* nameStart = line + 1;
                        auto* nameEnd   = nameStart;
                        while (*nameEnd != '\n') ++nameEnd;
                        return std::string{nameStart, nameEnd};
                    }
                }
            }
        }
    }
    return "Unknown";
}

void ReadPlayerInventory() {
    auto moduleBase         = 0x400000;  // Hardcoded for now
    auto staticCharacterPtr = moduleBase + 0x262844;

    auto playerInventoryPtr = Memory::Read<uint32_t>(staticCharacterPtr, {0x0, 0x34});

    uintptr_t itemPtr  = 0;
    size_t    quantity = 0;

    while (itemPtr != 0xCCCCCCCC) {
        itemPtr  = Memory::Read<uintptr_t>(playerInventoryPtr, 0x0);
        quantity = Memory::Read<uint32_t>(playerInventoryPtr, 0x4);
        playerInventoryPtr += 0x8;
        if (itemPtr == 0xCCCCCCCC) break;

        auto itemPID  = Memory::Read<uint32_t>(itemPtr, 0x64);
        auto itemName = GetNameOfItem(itemPID);
        Output("The player has {} items of item {} (ID {})\n", quantity, itemName, itemPID);
    }
}

void RunUI() {
    // auto injections = CodeInjection::RegisteredInjections;

    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        app.AddButton("Read Player Inventory", [&]() { ReadPlayerInventory(); });
        // for (auto [name, injection] : injections) {
        //     app.AddButton(string_format("Enable {}", injection->GetName()), [&, injection]() {
        //         injection->Toggle();
        //         if (injection->IsInstalled())
        //             app.ChangeButtonText(string_format("Disable {}", injection->GetName()));
        //         else
        //             app.ChangeButtonText(string_format("Enable {}", injection->GetName()));
        //     });
        // }
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    datFile = new DatFile{"D:\\GOG\\Games\\Fallout\\MASTER.DAT"};
    datFile->version();  // LOL
    // SetupHooks();
    RunUI();
    Injected_DLL::EjectDLL();
}

//     _.WriteAssembly(AssemblyCode {
//         code.mov(eax, ptr[esp + 0x4]);
//         code.nop();
//         code.nop();
//     })

// void SetupHooks() {
//     auto dropItemHook =
//         CodeInjection::New("Drop Item")
//             .Configure([](Injection& _) {
//                 _.Var<uintptr_t>("Detour", 0x46a41c);
//                 _.Var<size_t>("DetourSize", 5);
//                 _.Var<uintptr_t>(
//                     "JumpBack", _.Var<uintptr_t>("Detour") + _.Var<size_t>("DetourSize")
//                 );
//                 _.Var<uintptr_t>("Trampoline", 0);
//                 _.ReadBytes(
//                     {.addressVariable = "Detour",
//                      .outVariable     = "OriginalBytes",
//                      .byteCount       = _.Var<size_t>("DetourSize")}
//                 );
//             })
//             .OnInstall([](Injection& _) {
//                 // _.AllocateMemory({.addressVariable = "Trampoline", .block = [](Injection&)
//                 {}});
//                 _.WriteBytes({
//                     .addressVariable = "Detour",
//                     .bytes           = {0x69, 0x42, 0x69, 0x42, 0x69},
//                 });
//             })
//             .OnUninstall([](Injection& _) {
//                 _.WriteBytes({
//                     .addressVariable = "Detour",
//                     .bytesVariable   = "OriginalBytes",
//                 });
//             });
// }

// void BeginTrackingEntities() {
//     //
// }

// void PrintKnownEntities() {
//     //
// }

// void ClearKnownEntities() {
//     //
// }