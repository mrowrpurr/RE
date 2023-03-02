#pragma once

#include <Windows.h>
// ^ require Windows.h first

#include <TlHelp32.h>

namespace DLLInjection::Util {

    // https://stackoverflow.com/a/8032108
    // CC BY-SA 3.0
    const wchar_t* GetWideCharPtr(const char* c) {
        const size_t cSize = strlen(c) + 1;
        wchar_t*     wc    = new wchar_t[cSize];
        mbstowcs(wc, c, cSize);

        return wc;
    }

    DWORD GetProcId(const wchar_t* exeName) {
        // Get the process ID of the process that we want to inject our DLL into
        DWORD  procId = 0;
        HANDLE hSnap  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 procEntry;
            procEntry.dwSize = sizeof(procEntry);
            if (Process32First(hSnap, &procEntry)) {
                do {
                    if (!_wcsicmp(procEntry.szExeFile, exeName)) {
                        procId = procEntry.th32ProcessID;
                        break;
                    }
                } while (Process32Next(hSnap, &procEntry));
            }
        }
        CloseHandle(hSnap);
        return procId;
    }

    DWORD WaitForProcId(const wchar_t* exeName, DWORD intervalMs = 30) {
        DWORD procId = 0;
        while (!procId) {
            procId = GetProcId(exeName);
            Sleep(intervalMs);
        }
        return procId;
    }
}