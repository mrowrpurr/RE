#include <Windows.h>
//

//
#include <TlHelp32.h>

#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <string_view>

// ... can we use Boost libraries to make some of it less ... Windows-y?

template <class... Args>
void Print(const std::string_view text, Args&&... args) {
    std::cout << std::vformat(text, std::make_format_args(args...)) << std::endl;
}

DWORD GetProcId(const wchar_t* procName) {
    DWORD  procId = 0;
    HANDLE hSnap  = (CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!_wcsicmp(procEntry.szExeFile, procName)) {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName) {
    uintptr_t modBaseAddr = 0;
    HANDLE    hSnap       = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!_wcsicmp(modEntry.szModule, modName)) {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i) {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }
    return addr;
}

int main() {
    // Get Process ID
    DWORD procId = GetProcId(L"falloutwHR.exe");

    // Get Module Base Address
    uintptr_t modBaseAddr = GetModuleBaseAddress(procId, L"falloutwHR.exe");

    std::cout << "Module Base Address: 0x" << std::hex << modBaseAddr << std::endl;

    // Get Handle to Process
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    // Resolve the Base Address of the pointer (chain)
    uintptr_t dynamicPtrBaseAddr = modBaseAddr + 0x19CE50;

    Print("Base Address {:x}", dynamicPtrBaseAddr);

    // Resolve our pointer
    std::vector<unsigned int> offsets       = {0x2C};
    uintptr_t                 healthAddress = FindDMAAddy(hProc, dynamicPtrBaseAddr, offsets);

    Print("Health Address {:x}", healthAddress);

    // Read value
    int healthValue;
    ReadProcessMemory(hProc, (BYTE*)healthAddress, &healthValue, sizeof(healthValue), 0);
    Print("Health: {}", healthValue);

    // Write value
    int newValue = 5;
    WriteProcessMemory(hProc, (BYTE*)healthAddress, &newValue, sizeof(newValue), 0);

    // Read again
    ReadProcessMemory(hProc, (BYTE*)healthAddress, &healthValue, sizeof(healthValue), 0);
    Print("New Health: {}", newValue);

    // Close Handle
    CloseHandle(hProc);

    return 0;
}
