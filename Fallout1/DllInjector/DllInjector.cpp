#include <Windows.h>
//

#include <TlHelp32.h>

#include <iostream>

DWORD GetProcId(const char* procName) {
    DWORD  procId = 0;
    HANDLE hSnap  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!_stricmp(procEntry.szExeFile, procName)) {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

int main() {
    // update to be the name of your process
    const char* dllPath  = "C:\\Code\\mrowrpurr\\Retro-RE-Playground\\Fallout1\\DllInjector\\build\\LibraryToInject";
    auto        procName = "falloutwHR.exe";

    auto procId = 0;
    while (!procId) {
        procId = GetProcId(procName);
        Sleep(30);
    }

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
