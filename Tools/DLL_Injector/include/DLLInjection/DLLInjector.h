#pragma once

#include <Windows.h>
// ^ require Windows.h first

#include <TlHelp32.h>

#include <string>

#include "DLLInjection/Util.h"

namespace DLLInjection {
    void InjectDLL_CreateRemoteThread_LoadLibraryA(const wchar_t* exeName, const char* dllPath) {
        auto procId = Util::WaitForProcId(exeName);

        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);
        if (hProc && hProc != INVALID_HANDLE_VALUE) {
            void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
            WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);
            HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
            if (hThread) {
                CloseHandle(hThread);
            }
        }
    }

    void InjectDLL(const wchar_t* exeName, const char* dllPath) {
        InjectDLL_CreateRemoteThread_LoadLibraryA(exeName, dllPath);
    }
}
