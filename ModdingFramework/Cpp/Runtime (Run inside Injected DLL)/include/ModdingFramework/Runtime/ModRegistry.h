#pragma once

#include <Logging.h>
#include <StringFormatting.h>

#include <string>
#include <unordered_map>

#include "Mod.h"

namespace ModdingFramework::Runtime {

    class ModRegistry {
        std::unordered_map<std::string, std::unordered_map<std::string, Mod>> _mods;

        ModRegistry(const ModRegistry&)            = delete;
        ModRegistry(ModRegistry&&)                 = delete;
        ModRegistry& operator=(const ModRegistry&) = delete;
        ModRegistry& operator=(ModRegistry&&)      = delete;

    public:
        ModRegistry()  = default;
        ~ModRegistry() = default;

        void RegisterMod(Mod mod) {
            auto found = _mods.find(mod.GetName());
            if (found == _mods.end()) {
                _mods[mod.GetName()].emplace(mod.GetVersion(), std::move(mod));
            } else {
                auto foundVersion = found->second.find(mod.GetVersion());
                if (foundVersion == found->second.end()) {
                    found->second.emplace(mod.GetVersion(), std::move(mod));
                } else {
                    Log("Mod with name {} and version {} already registered", mod.GetName(),
                        mod.GetVersion());
                }
            }
        }

        void ForEachMod(std::function<void(Mod&)> callback) {
            for (auto& [name, versions] : _mods)
                for (auto& [version, mod] : versions) callback(mod);
        }
    };
}
