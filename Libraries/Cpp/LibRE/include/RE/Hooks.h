#pragma once

//
#include <form_app.h>
//

#include <RE/Helpers/FindByteSignatureAddress.h>
#include <string_format.h>

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "RE/Hooks/Detour32.h"
#include "RE/Hooks/Trampoline32.h"

namespace RE::Hooks {

    wchar_t* MODULE_NAME;
    DWORD    MODULE_BASE_ADDRESS = 0;

    namespace {

        // TODO jump back etc!
        void HookFunctionWrapper() {
            //
            FormApp::App().AppendOutput("HookFunctionWrapper() called");
        }
    }

    class Hook {
        // An arbitrary name for the hook (must be unique)
        std::string _name;

        // Whether or not the hook is enabled
        bool _enabled = false;

        // The length of the hook (number of bytes)
        unsigned int _length = 5;

        // Start address for a hook
        DWORD _address = 0;

        // The bytes to be overwritten by the hook
        std::vector<BYTE> _bytes;

        // A function to call when the hook is executed
        std::optional<std::function<void()>> _detourFunction;

        // Address of a detour function to call when the hook is executed
        BYTE* _detourFunctionAddress = 0;

        void FindBytes() {
            if (!_bytes.empty()) return;
            for (unsigned int i = 0; i < _length; i++) _bytes.push_back(*(BYTE*)(_address + i));
        }

    public:
        Hook() = default;

        // Hook(const std::string& name, DWORD address, BYTE* detourFunctionAddress)
        //     : _name(name), _address(address), _detourFunctionAddress(detourFunctionAddress) {}

        // Hook(const std::string& name, DWORD address) : _name(name), _address(address) {}

        Hook(const std::string& name, DWORD address, std::function<void()> detourFunction)
            : _name(name), _address(address), _detourFunction(detourFunction) {}

        void Install() {
            if (!_enabled) {
                // BLINDLY Overwrite the address with a jump to the detour function

                // Ok, but first, let's get the bytes...
                FindBytes();

                // TODO: overloads for detour please! like uintptr_t
                // Now, I guess write a jump to the function
                Detour32((BYTE*)_address, (BYTE*)HookFunctionWrapper, _length);

                // if (_detourFunctionAddress) {
                //     Detour32((BYTE*)_address, _detourFunctionAddress, _length);
                // } else if (_detourFunction) {
                //     Detour32((BYTE*)_address, _detourFunction.value(), _length);
                // } else {
                //     throw std::runtime_error("No detour function provided");
                // }

                //
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
            FindBytes();
            return _bytes;
        }
    };

    inline std::unordered_map<std::string, Hook> RegisteredHooks;

    // void Add(DWORD offset, BYTE* detourFunctionAddress) {
    //     auto name             = string_format("0x{:x}", offset);
    //     RegisteredHooks[name] = Hook(name, offset, detourFunctionAddress);
    // }

    void Add(DWORD offset, std::function<void()> detourFunction) {
        auto name             = string_format("0x{:x}", offset);
        RegisteredHooks[name] = Hook(name, offset, detourFunction);
    }

    Hook& Get(const std::string& name) { return RegisteredHooks[name]; }
}