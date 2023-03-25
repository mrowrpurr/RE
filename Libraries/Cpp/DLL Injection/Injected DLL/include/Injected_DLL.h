#pragma once

#include <Logging.h>
#include <Windows.h>

#include <thread>

DWORD __stdcall DllInjectionMainThread(PVOID base);

void OnDllInjection();

#define DLL_Main void OnDllInjection()

namespace Injected_DLL {
    HMODULE InjectedIntoModule;
    void    EjectDLL() { FreeLibraryAndExitThread(InjectedIntoModule, 0); }
}

DWORD __stdcall DllInjectionMainThread(PVOID base) {
    Injected_DLL::InjectedIntoModule = static_cast<HMODULE>(base);
    Log("Injected DLL main thread started (PID: {})", GetCurrentProcessId());
    Log("Module base address: {:x}", reinterpret_cast<uintptr_t>(Injected_DLL::InjectedIntoModule));
    Log("Calling OnDllInjection()");
    OnDllInjection();
    return 0;
}

int __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            Log("Injected DLL loaded into process (PID: {})", GetCurrentProcessId());
            CreateThread(nullptr, 0, DllInjectionMainThread, hModule, 0, nullptr);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return 1;
}

void EjectDLL() { Injected_DLL::EjectDLL(); }
