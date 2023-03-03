#pragma once

#include <RE/Helpers/FindByteSignatureAddress.h>
#include <string_format.h>

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "RE/Hooks/Detour32.h"
#include "RE/Hooks/Trampoline32.h"

namespace RE::Hooks {

    wchar_t* MODULE_NAME;
    DWORD    MODULE_BASE_ADDRESS = 0;

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
        std::function<void()> _detourFunction;

        void FindBytes() {
            if (!_bytes.empty()) return;
            for (unsigned int i = 0; i < _length; i++) _bytes.push_back(*(BYTE*)(_address + i));
        }

    public:
        Hook() = default;
        Hook(const std::string& name, DWORD address) : _name(name), _address(address) {}

        void Install() {
            if (!_enabled) {
                // BLINDLY Overwrite the address with a jump to the detour function

                // Ok, but first, let's get the bytes...
                FindBytes();

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

    void Add(DWORD offset, std::function<void()> hook) {
        auto name             = string_format("0x{:x}", offset);
        RegisteredHooks[name] = Hook(name, offset);
    }

    Hook& Get(const std::string& name) { return RegisteredHooks[name]; }
}