#include <DllInjector/DllInjector.h>
#include <Fallout1.h>
#include <psapi.h>  // For MODULEINFO
#include <unknwn.h>

#include <unordered_map>

#include "Print.h"

// typedef void (*WhateverThisMightContinueTheExistingCode)();

// WhateverThisMightContinueTheExistingCode originalCodez;

// // Where to jump back to!
// DWORD jumpBackAddy;

// void __declspec(naked) HookFunction() {
//     Print("Hello from the hook!");
//     __asm {
//         jmp [jumpBackAddy]
//     }
// }

// std::unordered_map<uintptr_t, bool> entityList;

// DWORD thisEntity = 0x0;
// DWORD collectEntitiesJumpBackAddy;

// // clang-format off
// __declspec(naked) void CollectEntitiesHookFunction() {
//     __asm {
//         xor eax,eax
//         mov ax,bx
//         mov thisEntity,edx
//         pushad
//     }

//     // I want edx

//     if (! entityList.contains(thisEntity))
//         entityList[thisEntity] = true;

//     __asm {
//         popad
//         jmp[collectEntitiesJumpBackAddy]
//     }
// }
// // clang-format on

// void FindEntityList() {
//     // 44D77A
//     auto module                 = L"falloutwHR.exe";
//     auto signature              = "\x89\xC2\x31\xC0\x66\x89\xD8\x80\xE4\xF7\xBE\xFF\xFF\xFF\xFF";
//     auto mask                   = "xxxxxxxxxxxxxxx";
//     auto startOffset            = 0x10000;
//     auto signatureAddress       = FindPattern(module, startOffset, signature, mask);
//     auto detourTargetAddress    = signatureAddress + 0x2;
//     collectEntitiesJumpBackAddy = detourTargetAddress + 0x5;

//     Print("Signature address: {:x}", signatureAddress);
//     Print("Detour target address: {:x}", detourTargetAddress);
//     Print("Jump back address: {:x}", collectEntitiesJumpBackAddy);

//     Detour32((BYTE*)detourTargetAddress, (BYTE*)CollectEntitiesHookFunction);
//     Print("Detour added!");
// }

// void InputLoop() {
//     while (true) {
//         if (GetAsyncKeyState(VK_HOME)) {
//             Print("HOME");
//             Print("Entity list size: {}", entityList.size());
//             for (auto& [key, value] : entityList) {
//                 Print("Entity: {:x}", key);
//             }
//         } else if (GetAsyncKeyState(VK_PRIOR)) {
//             Print("Page Down");
//         } else if (GetAsyncKeyState(VK_NEXT)) {
//             Print("Page Up");
//         }
//         Sleep(1000);
//     }
// }

// void DoHookingBadassery() {
//     Print("Hooking badassery");
//     auto hookLength      = 5;
//     auto hookAddress_AND = RE::GetModuleAddress(0x80D15);
//     jumpBackAddy         = (DWORD)hookAddress_AND + hookLength;
//     Detour32((BYTE*)hookAddress_AND, (BYTE*)HookFunction, 5);
//     Print("Detour added!");
// }

// void PrintOutFalloutStuff() {
//     auto& player = Fallout1::GetPlayer();

//     Print("NAME: {}", player.GetName());
//     Print("AGE: {}", player.GetAge());
//     auto count = player.GetInventoryCount();
//     Print("INVENTORY COUNT: {}", count);

//     auto items = player.GetInventoryItems();
//     for (auto& item : items) {
//         Print("ITEM PTR: {:x}", (uintptr_t)item.item);
//         Print("ITEM QUANTITY: {}", item.quantity);
//         Print("ITEM PID: {}", item.item->prototypeID);
//     }

//     // Find the address!
//     auto targetAddress = FindPattern(
//         L"falloutwHR.exe", 0x10000, "\x8B\x72\x04\xEB\x11\xBB\x01\x00\x00\x00\xBA\x00\x00\x00\x00\x89\xC8",
//         "xxxxxxxxxxx????xx"
//     );
//     Print("Found address: {:x}", targetAddress);
// }

void Injected_DLL_Main() { Fallout1::RE::MODULE_BASE = DllInjector::MODULE_BASE; }
