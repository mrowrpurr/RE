#include <DllInjector/DllInjector.h>
#include <Fallout1.h>
#include <unknwn.h>

#include "Print.h"

using namespace Fallout1;

void PrintOutFalloutStuff() {
    auto& player = Fallout1::GetPlayer();

    Print("NAME: {}", player.GetName());
    Print("AGE: {}", player.GetAge());
    auto count = player.GetInventoryCount();
    Print("INVENTORY COUNT: {}", count);

    auto items = player.GetInventoryItems();
    for (auto& item : items) {
        Print("ITEM QUANTITY: {}", item.quantity);
        Print("ITEM PID: {}", item.item->prototypeID);
    }
}

bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len) {
    if (len < 5) return false;
    DWORD curProtection;
    VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);
    uintptr_t relativeAddress         = dst - src - 5;
    *src                              = 0xE9;
    *(uintptr_t*)((uintptr_t)src + 1) = relativeAddress;
    VirtualProtect(src, len, curProtection, &curProtection);
    return true;
}

BYTE* TrampolineHook32(BYTE* src, BYTE* dst, const uintptr_t len) {
    if (len < 5) return 0;
    BYTE* gateway = (BYTE*)VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy_s(gateway, len, src, len);
    uintptr_t gatewayRelativeAddress            = src - gateway - 5;
    *(gateway + len)                            = 0xE9;
    *(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddress;
    Detour32(src, dst, len);
    Print("Gateway at: {:x}", (uintptr_t)gateway);
    return gateway;
}

typedef void (*WhateverThisMightContinueTheExistingCode)();

WhateverThisMightContinueTheExistingCode originalCodez;

// Where to jump back to!
DWORD jumpBackAddy;

void __declspec(naked) HookFunction() {
    Print("Hello from the hook!");
    __asm {
        jmp [jumpBackAddy]
    }
}

void DoHookingBadassery() {
    Print("Hooking badassery");
    auto hookLength      = 5;
    auto hookAddress_AND = RE::GetModuleAddress(0x80D15);
    jumpBackAddy         = (DWORD)hookAddress_AND + hookLength;
    Detour32((BYTE*)hookAddress_AND, (BYTE*)HookFunction, 5);
    Print("Detour added!");
}

void Injected_DLL_Main() {
    Fallout1::RE::MODULE_BASE = DllInjector::MODULE_BASE;
    DoHookingBadassery();
}
