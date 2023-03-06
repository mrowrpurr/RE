#pragma once

#include <Windows.h>

#include <thread>

DWORD __stdcall DllInjectionMainThread(PVOID base);

void OnDllInjection();

#define DLL_Main void OnDllInjection()

namespace Injected_DLL {
    HMODULE         InjectedIntoModule;
    std::thread::id InjectedIntoThreadID = std::this_thread::get_id();
    size_t          InjectedIntoThreadIDT;
    void            EjectDLL() { FreeLibraryAndExitThread(InjectedIntoModule, 0); }
}

DWORD __stdcall DllInjectionMainThread(PVOID base) {
    Injected_DLL::InjectedIntoModule = static_cast<HMODULE>(base);
    OnDllInjection();
    return 0;
}

int __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            Injected_DLL::InjectedIntoThreadIDT = std::hash<std::thread::id>{}(std::this_thread::get_id());
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
