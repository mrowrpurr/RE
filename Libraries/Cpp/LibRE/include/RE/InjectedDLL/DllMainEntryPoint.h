#pragma once

#include <Windows.h>

DWORD __stdcall DllInjectionMainThread(PVOID base);

int __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(nullptr, 0, DllInjectionMainThread, hModule, 0, nullptr);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return 1;
}