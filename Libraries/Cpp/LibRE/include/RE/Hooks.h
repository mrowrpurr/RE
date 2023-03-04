#pragma once

//
#include <form_app.h>
//

#include <RE/Helpers/FindByteSignatureAddress.h>
#include <string_format.h>
#include <xbyak/xbyak.h>

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "RE/Hooks/Detour32.h"
#include "RE/Hooks/Trampoline32.h"
#include "RE/Util.h"

namespace RE::Hooks {

    std::function<void()> THE_HOOK_LAMBDA;

    void RUN_THE_LAMBDA() { THE_HOOK_LAMBDA(); }

    wchar_t* MODULE_NAME;
    DWORD    MODULE_BASE_ADDRESS = 0;

    namespace {
        DWORD AddressOf_OriginalBytes = 0;
        DWORD AddressOf_JumpBack      = 0;

        struct HookFunctionWrapper_JumpBackCode : Xbyak::CodeGenerator {
            HookFunctionWrapper_JumpBackCode() {
                // jmp((void*)CurrentJumpBackAddressForHookFunctionWrapper);
            }
        };

        void __declspec(naked) HookStart() {
            // JMP
            // OTHER
        }

        void HookBody() {}

        void HookEnd() {
            //
        }
    }

    class Hook {
        // An arbitrary name for the hook (must be unique)
        std::string _name;

        // Whether or not the hook is enabled
        bool _enabled = false;

        // The length of the hook (number of bytes)
        unsigned long _length = 5;

        // Start address for a hook
        DWORD _address = 0;

        // Address to jump back to after the hook is executed
        DWORD _jumpBackAddress = 0;

        // The bytes to be overwritten by the hook
        std::vector<BYTE> _bytes;

        // Address to the bytes which were overwritten by the hook
        DWORD _newLocationOfOriginalBytes = 0;

        // A function to call when the hook is executed
        std::optional<std::function<void()>> _detourFunction;

        // Address of a detour function to call when the hook is executed
        // DWORD_PTR _detourFunctionAddress = 0;

        void ReadOriginalBytes() {
            if (!_bytes.empty()) return;
            for (unsigned int i = 0; i < _length; i++) _bytes.push_back(*(BYTE*)(_address + i));
        }

    public:
        Hook() = default;

        Hook(const std::string& name, DWORD address, std::function<void()> detourFunction)
            : _name(name), _address(address), _detourFunction(detourFunction) {}

        // Hook(const std::string& name, DWORD address, DWORD_PTR detourFunctionAddress)
        //     : _name(name), _address(address), _detourFunctionAddress(detourFunctionAddress) {}

        void Install() {
            if (!_enabled) {
                ReadOriginalBytes();

                auto size = _bytes.size() + 1 + 5 + 1 + 5;  // 1 byte for pushad, 5 bytes for call, 1 byte for popad,
                // auto size = _bytes.size() + 1 + 1 + 5;  // 1 byte for pushad, 1 byte for popad, 5 bytes for jmp

                auto memory = (LPBYTE)VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
                memcpy_s(memory, _bytes.size(), _bytes.data(), _bytes.size());

                auto offset = _bytes.size();

                memory[offset] = 0x60;  // pushad
                offset++;

                memory[offset] = 0xE8;  // call
                offset++;

                THE_HOOK_LAMBDA             = _detourFunction.value();
                DWORD_PTR myFunctionAddress = reinterpret_cast<DWORD_PTR>(RUN_THE_LAMBDA);

                auto relativeDetourFunctionAddress        = myFunctionAddress - ((DWORD)memory + offset - 1) - 5;
                *(uintptr_t*)((uintptr_t)&memory[offset]) = (uintptr_t)relativeDetourFunctionAddress;
                offset += 4;

                memory[offset] = 0x61;  // popad
                offset++;

                memory[offset] = 0xE9;  // jmp
                offset++;

                auto relativeAddress = (_address + 5) - ((DWORD)memory + offset - 1) - 5;  // cause we're adding 5 bytes
                *(uintptr_t*)((uintptr_t)&memory[offset]) = (uintptr_t)relativeAddress;

                // [HOOK_BYTES_LOCATION]   aa bb cc dd ee   <---- Original Bytes
                //         pushad
                //         call <hook function>
                //         popad
                //         jmp <jump back address>

                Detour32((BYTE*)_address, (BYTE*)memory, 5);

                _enabled = true;
            }
        }

        void Uninstall() {
            if (_enabled) {
                _enabled = false;
            }
        }

        bool Toggle() {
            if (_enabled) {
                Uninstall();
            } else {
                Install();
            }
            return _enabled;
        }

        std::vector<BYTE> GetBytes() {
            ReadOriginalBytes();
            return _bytes;
        }
    };

    inline std::unordered_map<std::string, Hook> RegisteredHooks;

    // void Add(DWORD offset, DWORD_PTR detourFunctionAddress) {
    //     auto name             = string_format("0x{:x}", offset);
    //     RegisteredHooks[name] = Hook(name, offset, detourFunctionAddress);
    // }

    void Add(DWORD offset, std::function<void()> detourFunction) {
        auto name             = string_format("0x{:x}", offset);
        RegisteredHooks[name] = Hook(name, offset, detourFunction);
    }

    Hook& Get(const std::string& name) { return RegisteredHooks[name]; }
}

// Util::JIT(someBytes);

// HookFunctionWrapper_JumpBackCode jitFactory;
// void (*jitCode)() = jitFactory.getCode<void (*)()>();
// jitCode();

// __asm {
//     jmp[CurrentJumpBackAddressForHookFunctionWrapper]
// }