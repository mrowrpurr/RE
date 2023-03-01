#pragma once

#include <TlHelp32.h>
#include <stdint.h>
#include <windows.h>

#include <iostream>
#include <thread>
#include <vector>

// Implement this function to run your code!
void Injected_DLL_Main();

namespace DllInjector {

    namespace Util {
        // https://stackoverflow.com/a/8032108
        // CC BY-SA 3.0
        const wchar_t* GetWideCharPtr(const char* c) {
            const size_t cSize = strlen(c) + 1;
            wchar_t*     wc    = new wchar_t[cSize];
            mbstowcs(wc, c, cSize);

            return wc;
        }
    }

    uintptr_t MODULE_BASE;

    // Main Thread
    DWORD __stdcall MainThread(PVOID base) {
        auto module = static_cast<HMODULE>(base);

        auto processName = std::getenv("DLL_INJECT_EXE");
        if (!processName) {
            MessageBoxA(0, "DLL_INJECT_EXE not set", "DLL_INJECT_EXE not set", MB_OK);
            FreeLibraryAndExitThread(module, 0);
            return 0;
        }

        auto wideProcessName = Util::GetWideCharPtr(processName);

        AllocConsole();
        FILE* f;
        freopen_s(&f, "CONOUT$", "w", stdout);
        MODULE_BASE = (uintptr_t)GetModuleHandle(wideProcessName);

        // Call your stuff!
        try {
            Injected_DLL_Main();
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown Exception" << std::endl;
        }

        MessageBoxA(0, "Close to eject .dll", "Close to eject .dll", MB_OK);
        fclose(f);
        FreeConsole();
        FreeLibraryAndExitThread(module, 0);
    }
}

// Entry Point
int __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(nullptr, 0, DllInjector::MainThread, hModule, 0, nullptr);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return 1;
}