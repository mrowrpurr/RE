#pragma once

//
#include <form_app.h>
//

#include <RE/Helpers/FindByteSignatureAddress.h>
#include <string_format.h>
#include <xbyak/xbyak.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "RE/Hooks/Detour32.h"
#include "RE/Hooks/Trampoline32.h"
#include "RE/Util.h"

namespace RE::Hooks {

    /** [BEGIN] Refactor me! */
    DWORD             CURRENT_REGISTER_VALUE_EAX   = 0;
    DWORD             CURRENT_REGISTER_VALUE_EBX   = 0;
    DWORD             CURRENT_REGISTER_VALUE_ECX   = 0;
    DWORD             CURRENT_REGISTER_VALUE_EDX   = 0;
    DWORD             CURRENT_REGISTER_VALUE_ESI   = 0;
    DWORD             CURRENT_REGISTER_VALUE_EDI   = 0;
    DWORD             CURRENT_REGISTER_VALUE_EBP   = 0;
    DWORD             CURRENT_REGISTER_VALUE_ESP   = 0;
    std::vector<BYTE> MOV_REGISTER_INSTRUCTION_EAX = {0xA3};
    std::vector<BYTE> MOV_REGISTER_INSTRUCTION_EBX = {0x89, 0x1D};
    std::vector<BYTE> MOV_REGISTER_INSTRUCTION_ECX = {0x89, 0x0D};
    std::vector<BYTE> MOV_REGISTER_INSTRUCTION_EDX = {0x89, 0x15};
    std::vector<BYTE> MOV_REGISTER_INSTRUCTION_ESI = {0x89, 0x35};
    std::vector<BYTE> MOV_REGISTER_INSTRUCTION_EDI = {0x89, 0x3D};
    std::vector<BYTE> MOV_REGISTER_INSTRUCTION_EDP = {0x89, 0x2D};
    std::vector<BYTE> MOV_REGISTER_INSTRUCTION_ESP = {0x89, 0x25};
    class Registers {
        Registers()                            = default;
        ~Registers()                           = default;
        Registers(const Registers&)            = delete;
        Registers(Registers&&)                 = delete;
        Registers& operator=(const Registers&) = delete;
        Registers& operator=(Registers&&)      = delete;

    public:
        static Registers& GetCurrent() {
            static Registers singleton;
            return singleton;
        }
        DWORD eax() { return CURRENT_REGISTER_VALUE_EAX; }
        DWORD ebx() { return CURRENT_REGISTER_VALUE_EBX; }
        DWORD ecx() { return CURRENT_REGISTER_VALUE_ECX; }
        DWORD edx() { return CURRENT_REGISTER_VALUE_EDX; }
        DWORD esi() { return CURRENT_REGISTER_VALUE_ESI; }
        DWORD edi() { return CURRENT_REGISTER_VALUE_EDI; }
        DWORD ebp() { return CURRENT_REGISTER_VALUE_EBP; }
        DWORD esp() { return CURRENT_REGISTER_VALUE_ESP; }
    };
    std::function<void(Registers&)> THE_HOOK_LAMBDA;
    void                            RUN_THE_LAMBDA() { THE_HOOK_LAMBDA(Registers::GetCurrent()); }
    /** [END] Refactor me! */

    constexpr auto DEFAULT_HOOK_LENGTH = 5;
    wchar_t*       MODULE_NAME;
    DWORD          MODULE_BASE_ADDRESS = 0;

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
        unsigned int _length = 0;

        // Start address for a hook
        DWORD _address = 0;

        // Address to jump back to after the hook is executed
        DWORD _jumpBackAddress = 0;

        // The bytes to be overwritten by the hook
        std::vector<BYTE> _bytes;

        // Address to the bytes which were overwritten by the hook
        DWORD _newLocationOfOriginalBytes = 0;

        // A function to call when the hook is executed
        std::optional<std::function<void(Registers&)>> _detourFunction;

        // Address of a detour function to call when the hook is executed
        // DWORD_PTR _detourFunctionAddress = 0;

        void ReadOriginalBytes() {
            if (!_bytes.empty()) return;
            for (unsigned int i = 0; i < _length; i++) _bytes.push_back(*(BYTE*)(_address + i));
        }

    public:
        Hook(
            const std::string& name, DWORD address, unsigned int length, std::function<void(Registers&)> detourFunction
        )
            : _name(name), _address(address), _length(length), _detourFunction(detourFunction) {}

        // Hook(const std::string& name, DWORD address, DWORD_PTR detourFunctionAddress)
        //     : _name(name), _address(address), _detourFunctionAddress(detourFunctionAddress) {}

        void Install() {
            if (!_enabled) {
                ReadOriginalBytes();

                auto registerMovInstructionsTotalSize =
                    MOV_REGISTER_INSTRUCTION_EAX.size() + MOV_REGISTER_INSTRUCTION_EBX.size() +
                    MOV_REGISTER_INSTRUCTION_ECX.size() + MOV_REGISTER_INSTRUCTION_EDX.size() +
                    MOV_REGISTER_INSTRUCTION_ESI.size() + MOV_REGISTER_INSTRUCTION_EDI.size() +
                    MOV_REGISTER_INSTRUCTION_EDP.size() + MOV_REGISTER_INSTRUCTION_ESP.size();

                auto size = _bytes.size() + registerMovInstructionsTotalSize + 1 + 5 + 1 +
                            5;  // <original bytes>, <mov register bytes>, 1 byte for pushad, 5 bytes for call, 1 byte
                                // for popad,

                auto memory = (LPBYTE)VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
                memcpy_s(memory, _bytes.size(), _bytes.data(), _bytes.size());
                auto offset = _bytes.size();

                // Copy the registers
                memcpy_s(
                    memory + offset, MOV_REGISTER_INSTRUCTION_EAX.size(), MOV_REGISTER_INSTRUCTION_EAX.data(),
                    MOV_REGISTER_INSTRUCTION_EAX.size()
                );
                offset += MOV_REGISTER_INSTRUCTION_EAX.size();
                *(uintptr_t*)((uintptr_t)&memory[offset]) = (uintptr_t)&CURRENT_REGISTER_VALUE_EAX;
                offset += sizeof(DWORD);  // maybe this style is better

                memcpy_s(
                    memory + offset, MOV_REGISTER_INSTRUCTION_EBX.size(), MOV_REGISTER_INSTRUCTION_EBX.data(),
                    MOV_REGISTER_INSTRUCTION_EBX.size()
                );
                offset += MOV_REGISTER_INSTRUCTION_EBX.size();
                *(uintptr_t*)((uintptr_t)&memory[offset]) = (uintptr_t)&CURRENT_REGISTER_VALUE_EBX;
                offset += 4;

                memcpy_s(
                    memory + offset, MOV_REGISTER_INSTRUCTION_ECX.size(), MOV_REGISTER_INSTRUCTION_ECX.data(),
                    MOV_REGISTER_INSTRUCTION_ECX.size()
                );
                offset += MOV_REGISTER_INSTRUCTION_ECX.size();
                *(uintptr_t*)((uintptr_t)&memory[offset]) = (uintptr_t)&CURRENT_REGISTER_VALUE_ECX;
                offset += 4;

                memcpy_s(
                    memory + offset, MOV_REGISTER_INSTRUCTION_EDX.size(), MOV_REGISTER_INSTRUCTION_EDX.data(),
                    MOV_REGISTER_INSTRUCTION_EDX.size()
                );
                offset += MOV_REGISTER_INSTRUCTION_EDX.size();
                *(uintptr_t*)((uintptr_t)&memory[offset]) = (uintptr_t)&CURRENT_REGISTER_VALUE_EDX;
                offset += 4;

                memcpy_s(
                    memory + offset, MOV_REGISTER_INSTRUCTION_ESI.size(), MOV_REGISTER_INSTRUCTION_ESI.data(),
                    MOV_REGISTER_INSTRUCTION_ESI.size()
                );
                offset += MOV_REGISTER_INSTRUCTION_ESI.size();
                *(uintptr_t*)((uintptr_t)&memory[offset]) = (uintptr_t)&CURRENT_REGISTER_VALUE_ESI;
                offset += 4;

                memcpy_s(
                    memory + offset, MOV_REGISTER_INSTRUCTION_EDI.size(), MOV_REGISTER_INSTRUCTION_EDI.data(),
                    MOV_REGISTER_INSTRUCTION_EDI.size()
                );
                offset += MOV_REGISTER_INSTRUCTION_EDI.size();
                *(uintptr_t*)((uintptr_t)&memory[offset]) = (uintptr_t)&CURRENT_REGISTER_VALUE_EDI;
                offset += 4;

                memcpy_s(
                    memory + offset, MOV_REGISTER_INSTRUCTION_EDP.size(), MOV_REGISTER_INSTRUCTION_EDP.data(),
                    MOV_REGISTER_INSTRUCTION_EDP.size()
                );
                offset += MOV_REGISTER_INSTRUCTION_EDP.size();
                *(uintptr_t*)((uintptr_t)&memory[offset]) = (uintptr_t)&CURRENT_REGISTER_VALUE_EBP;
                offset += 4;

                memcpy_s(
                    memory + offset, MOV_REGISTER_INSTRUCTION_ESP.size(), MOV_REGISTER_INSTRUCTION_ESP.data(),
                    MOV_REGISTER_INSTRUCTION_ESP.size()
                );
                offset += MOV_REGISTER_INSTRUCTION_ESP.size();
                *(uintptr_t*)((uintptr_t)&memory[offset]) = (uintptr_t)&CURRENT_REGISTER_VALUE_ESP;
                offset += 4;

                // ...
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
                // <--- SAVE DEM REGISTER VALUES!
                //         pushad
                //         call <hook function>
                //         popad
                //         jmp <jump back address>

                Detour32((BYTE*)_address, (BYTE*)memory, _length);

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

        DWORD_PTR GetAddress() { return _address; }

        std::vector<BYTE> GetBytes() {
            ReadOriginalBytes();
            return _bytes;
        }
    };

    std::unordered_map<std::string, std::shared_ptr<Hook>> RegisteredHooks;

    // void Add(DWORD offset, DWORD_PTR detourFunctionAddress) {
    //     auto name             = string_format("0x{:x}", offset);
    //     RegisteredHooks[name] = Hook(name, offset, detourFunctionAddress);
    // }

    std::shared_ptr<Hook> Add(
        const std::string& name, DWORD offset, unsigned int length, std::function<void(Registers&)> detourFunction
    ) {
        auto hook             = std::make_shared<Hook>(name, offset, length, detourFunction);
        RegisteredHooks[name] = hook;
        return hook;
    }

    std::shared_ptr<Hook> Add(const std::string& name, DWORD offset, std::function<void(Registers&)> detourFunction) {
        return Add(name, offset, DEFAULT_HOOK_LENGTH, detourFunction);
    }

    // void Add(DWORD offset, std::function<void()> detourFunction) {
    //     Add(string_format("0x{:x}", offset), offset, detourFunction);
    // }

    std::shared_ptr<Hook> Get(const std::string& name) { return RegisteredHooks.at(name); }
}

// Util::JIT(someBytes);

// HookFunctionWrapper_JumpBackCode jitFactory;
// void (*jitCode)() = jitFactory.getCode<void (*)()>();
// jitCode();

// __asm {
//     jmp[CurrentJumpBackAddressForHookFunctionWrapper]
// }