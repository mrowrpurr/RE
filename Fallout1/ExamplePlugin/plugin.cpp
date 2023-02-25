#include <DllInjector/DllInjector.h>
#include <Fallout1.h>
#include <unknwn.h>

#include "Print.h"

using namespace Fallout1;

void PrintOutFalloutStuff() {
    Fallout1::RE::MODULE_BASE = DllInjector::MODULE_BASE;

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

bool Detour32(BYTE* src, const BYTE* dst, const uintptr_t len) {
    if (len < 5) return false;

    // Write NOPs to the beginning of the function
    DWORD curProtection;
    VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

    uintptr_t relativeAddress = dst - src - 5;  // 5 = JMP opcode size

    *src                   = 0xE9;             // JMP opcode
    *(uintptr_t*)(src + 1) = relativeAddress;  // JMP address

    // Restore the original protection
    DWORD temp;
    VirtualProtect(src, len, curProtection, &temp);

    return true;
}

BYTE* TrampolineHook32(BYTE* src, BYTE* dst, const uintptr_t len) {
    if (len < 5) return 0;

    // Allocate memory for the gateway
    BYTE* gateway = (BYTE*)VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    // Write the bytes that will be overwritten
    memcpy(gateway, src, len);

    // Get the gateway to destination address
    uintptr_t gatewayRelativeAddr = src - gateway - 5;

    // Write the JMP opcode
    gateway[len] = 0xE9;

    // Write the address
    *(uintptr_t*)(gateway + len + 1) = gatewayRelativeAddr;

    // Write the NOPs
    for (uintptr_t i = 0; i < len; i++) {
        src[i] = 0x90;
    }

    // Write the JMP opcode
    *src = 0xE9;

    // Write the address
    *(uintptr_t*)(src + 1) = (uintptr_t)(dst - src) - 5;

    return gateway;
}

typedef void (*WhateverThisMightContinueTheExistingCode)();

WhateverThisMightContinueTheExistingCode originalCodez;

void ThisIsOurHook() { Print("OMFG This is our hook!"); }

void DoHookingBadassery() {
    Print("This isn't goint to work...");
    // Address of the AND instruction to insert our hook at
    WhateverThisMightContinueTheExistingCode addressOfTheAND =
        (WhateverThisMightContinueTheExistingCode)RE::GetModuleAddress(0x18AA2);
    originalCodez =
        (WhateverThisMightContinueTheExistingCode)TrampolineHook32((BYTE*)addressOfTheAND, (BYTE*)ThisIsOurHook, 5);
}

void Injected_DLL_Main() { DoHookingBadassery(); }
