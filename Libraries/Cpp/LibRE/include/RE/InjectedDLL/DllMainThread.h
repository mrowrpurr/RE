#pragma once

#include <Windows.h>

#include "RE/InjectedDLL/Module.h"

void OnDllInjection();

DWORD __stdcall DllInjectionMainThread(PVOID base) {
    RE::InjectedDLL::InjectedIntoModule = static_cast<HMODULE>(base);
    OnDllInjection();
    return 0;
}
