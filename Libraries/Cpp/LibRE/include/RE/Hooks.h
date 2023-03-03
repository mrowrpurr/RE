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
        std::string _name;
        DWORD       _address;
        bool        _enabled = false;

    public:
        Hook() = default;
        Hook(const std::string& name, DWORD address) : _name(name), _address(address) {}

        void Install() {
            if (!_enabled) {
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
    };

    inline std::unordered_map<std::string, Hook> RegisteredHooks;

    void Add(DWORD offset, std::function<void()> hook) {
        auto name             = string_format("0x{:x}", offset);
        RegisteredHooks[name] = Hook(name, offset);
    }

    Hook& Get(const std::string& name) { return RegisteredHooks[name]; }
}