#pragma once

#include <Windows.h>

#include "DLLInjection/InjectedDLL/Module.h"

void OnDllInjection();

DWORD __stdcall DllInjectionMainThread(PVOID base) {
    DLLInjection::InjectedIntoModule = static_cast<HMODULE>(base);
    OnDllInjection();
    return 0;
}
