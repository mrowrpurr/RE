#include <windows.h>
//

#include <TlHelp32.h>

#include <chrono>
#include <format>
#include <iostream>
#include <thread>
#include <vector>


constexpr auto PROCESS_NAME = L"falloutwHR.exe";

// Find Dynamic Memory Allocation Address
uintptr_t GetAddress(uintptr_t base, const std::vector<uintptr_t>& offsets) {
    uintptr_t address = base;
    for (auto offset : offsets) {
        address = *reinterpret_cast<uintptr_t*>(address) + offset;
    }
    return address;
}

// Main Thread
DWORD __stdcall mainThread(PVOID base) {
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(PROCESS_NAME);
    //
    auto module = static_cast<HMODULE>(base);
    MessageBoxA(0, std::format("The module base is {:x}", moduleBase).c_str(), "DLL Message", MB_OK);
    std::this_thread::sleep_for(std::chrono::seconds(5));
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