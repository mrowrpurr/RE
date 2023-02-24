#include <windows.h>

#include <chrono>
#include <thread>

DWORD __stdcall mainThread(PVOID base) {
    auto module = static_cast<HMODULE>(base);
    MessageBoxA(0, "CHANGE IT AGAIN", "DLL Message", MB_OK);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    FreeLibraryAndExitThread(module, 0);
}

int __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
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