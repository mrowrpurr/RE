#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Hooks/Hook.h"

namespace Hooks {

    class HookRegistry {
        // Represents a collection of hooks which can be added and removed
        std::unordered_map<std::string, std::shared_ptr<Hook>> RegisteredHooks;

        HookRegistry()                               = default;
        ~HookRegistry()                              = default;
        HookRegistry(const HookRegistry&)            = delete;
        HookRegistry(HookRegistry&&)                 = delete;
        HookRegistry& operator=(const HookRegistry&) = delete;
        HookRegistry& operator=(HookRegistry&&)      = delete;

    public:
        static HookRegistry& GetSingleton() {
            static HookRegistry singleton;
            return singleton;
        }

        std::shared_ptr<Hook> RegisterHook(const std::string& name) {
            if (RegisteredHooks.find(name) != RegisteredHooks.end()) return RegisteredHooks[name];
            auto hook             = std::make_shared<Hook>();
            RegisteredHooks[name] = hook;
            return hook;
        }

        std::shared_ptr<Hook> GetHook(const std::string& name) {
            if (RegisteredHooks.find(name) != RegisteredHooks.end()) return RegisteredHooks[name];
            return nullptr;
        }

        std::unordered_map<std::string, std::shared_ptr<Hook>>& GetHooks() { return RegisteredHooks; }
    };
}
