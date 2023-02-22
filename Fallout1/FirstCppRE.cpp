// Include *before* TlHelp32.h
#include <Windows.h>
//

#include <TlHelp32.h>

#include <format>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

constexpr auto PROCESS_NAME = L"fallout2HR.exe";

// ... can we use Boost libraries to make some of it less ... Windows-y?

template <class... Args>
void Print(const std::string_view text, Args&&... args) {
    std::cout << std::vformat(text, std::make_format_args(args...)) << std::endl;
}

namespace RE {
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
}

namespace Fallout2 {
    HANDLE    _handle = nullptr;
    DWORD     GetProdID() { return RE::GetProcId(PROCESS_NAME); }
    uintptr_t GetModuleBaseAddress() { return RE::GetModuleBaseAddress(GetProdID(), PROCESS_NAME); }
    void      UsingProcess(std::function<void()> func) {
        _handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, GetProdID());
        func();
        CloseHandle(_handle);
    }
    uintptr_t GetAddress(unsigned int baseAddress, std::vector<unsigned int> offsets = {}) {
        return RE::FindDMAAddy(_handle, GetModuleBaseAddress() + baseAddress, offsets);
    }

    int GetNumberOfItemsInInventory() {
        int result;
        UsingProcess([&]() {
            int       itemNumberAddress;
            uintptr_t pointerAddress = GetAddress(0x19E960);
            ReadProcessMemory(_handle, (BYTE*)pointerAddress, &itemNumberAddress, sizeof(itemNumberAddress), 0);
            ReadProcessMemory(_handle, (BYTE*)itemNumberAddress, &result, sizeof(result), 0);
        });
        return result;
    }
}

void DoReverseEngineeringShit() {
    // int healthValue;
    // ReadProcessMemory(hProc, (BYTE*)healthAddress, &healthValue, sizeof(healthValue), 0);
    // Print("Health: {}", healthValue);

    // int newValue = 69;
    // WriteProcessMemory(hProc, (BYTE*)healthAddress, &newValue, sizeof(newValue), 0);
}

int main() {
    Print("Your character currently has {} items in their inventory.", Fallout2::GetNumberOfItemsInInventory());
    return 0;
}
