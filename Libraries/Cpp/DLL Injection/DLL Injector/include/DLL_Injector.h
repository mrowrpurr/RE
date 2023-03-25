#pragma once

#include <Windows.h>
// ^ require Windows.h first

#include <Logging.h>
#include <TlHelp32.h>

#include <filesystem>
#include <string>

namespace DLL_Injector {

    namespace Util {

        DWORD GetProcId(const std::string& exeName) {
            DWORD  procId = 0;
            HANDLE hSnap  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            if (hSnap != INVALID_HANDLE_VALUE) {
                PROCESSENTRY32 procEntry;
                procEntry.dwSize = sizeof(procEntry);
                if (Process32First(hSnap, &procEntry)) {
                    do {
                        if (!_stricmp(procEntry.szExeFile, exeName.c_str())) {
                            procId = procEntry.th32ProcessID;
                            break;
                        }
                    } while (Process32Next(hSnap, &procEntry));
                }
            }
            CloseHandle(hSnap);
            return procId;
        }

        DWORD WaitForProcId(const std::string& exeName, DWORD intervalMs = 30) {
            DWORD procId = 0;
            while (!procId) {
                procId = GetProcId(exeName);
                Sleep(intervalMs);
            }
            return procId;
        }

        bool IsProcessRunning(const std::string& exeName) { return GetProcId(exeName) != 0; }
    }

    namespace Techniques {

        // TODO: add option for whether to WAIT for the process (or preferably don't wait at all!)
        void InjectDLL_CreateRemoteThread_LoadLibraryA(
            const std::string& exeName, const std::string& dllPath
        ) {
            auto procId = Util::WaitForProcId(exeName);
            Log("Injecting DLL '{}' into process '{}' (PID: {})", dllPath, exeName, procId);

            HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);
            if (hProc && hProc != INVALID_HANDLE_VALUE) {
                void* loc =
                    VirtualAllocEx(hProc, 0, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
                WriteProcessMemory(hProc, loc, dllPath.c_str(), dllPath.size() + 1, 0);
                HANDLE hThread = CreateRemoteThread(
                    hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0
                );
                if (hThread) CloseHandle(hThread);
            }
        }
    }

    void InjectDLL(const std::string& exeName, const std::string& dllPath) {
        if (!std::filesystem::exists(dllPath)) {
            Log("DLL does not exist: {}", dllPath);
            return;
        }
        auto absoluteDllPath = std::filesystem::absolute(dllPath).string();
        Techniques::InjectDLL_CreateRemoteThread_LoadLibraryA(exeName, absoluteDllPath);
    }
}