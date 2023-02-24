#include <windows.h>
//

#include <TlHelp32.h>
#include <stdint.h>

#include <chrono>
#include <format>
#include <iostream>
#include <thread>
#include <vector>

constexpr auto PROCESS_NAME = L"falloutwHR.exe";
uintptr_t      MODULE_BASE;

// Find Dynamic Memory Allocation Address
uintptr_t GetAddress(uintptr_t base, const std::vector<uintptr_t>& offsets = {}) {
    uintptr_t address = MODULE_BASE + base;
    for (auto offset : offsets) {
        address = *reinterpret_cast<uintptr_t*>(address) + offset;
    }
    return address;
}

template <class... Args>
void MsgBox(const std::string_view text, Args&&... args) {
    auto message = std::vformat(text, std::make_format_args(args...));
    MessageBoxA(0, message.c_str(), "Our Sweet Fallout Injected DLL", MB_OK);
}

struct Player {
    uint32_t unk00;
    uint32_t maybeMapHex;
    uint32_t unk08;
    uint32_t unk0C;
    uint32_t screenScrollY;
    uint32_t screenScrollX;
    uint32_t unk18;
    uint32_t characterDirection;
    uint32_t unk20Ptr;
    uint32_t unk24;
    uint32_t unk28;
    uint32_t inventoryCount;
    uint32_t unk30;
    uint32_t unk34;
    uint32_t inventoryPtr;
    uint32_t unk3C;
    uint32_t actionPoints;
};

void DoCoolStuff() {
    auto* player = reinterpret_cast<Player*>(GetAddress(0x105734, {0x0}));
    MsgBox("INVENTORY COUNT is: {}", player->inventoryCount);
}

// Main Thread
DWORD __stdcall mainThread(PVOID base) {
    MODULE_BASE = (uintptr_t)GetModuleHandle(PROCESS_NAME);
    DoCoolStuff();
    auto module = static_cast<HMODULE>(base);
    MessageBoxA(0, "Close to eject", "Our Sweet Fallout Injected DLL", MB_OK);
    FreeLibraryAndExitThread(module, 0);
}

// Entry Point
int __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(nullptr, 0, mainThread, hModule, 0, nullptr);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return 1;
}