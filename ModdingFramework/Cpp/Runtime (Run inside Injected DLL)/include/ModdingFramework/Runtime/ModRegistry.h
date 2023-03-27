#pragma once

#include <Logging.h>
#include <ModdingFramework\IModRegistry.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "Mod.h"

namespace ModdingFramework::Runtime {

    class ModRegistry {
        ModRegistry(const ModRegistry&)            = delete;
        ModRegistry(ModRegistry&&)                 = delete;
        ModRegistry& operator=(const ModRegistry&) = delete;
        ModRegistry& operator=(ModRegistry&&)      = delete;

        std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<Mod>>>
            _registeredMods;

    public:
        ModRegistry()  = default;
        ~ModRegistry() = default;

        void RegisterMod(
            const char* modName, const char* version, const char* type, const char* source,
            const char* folder
        ) {
            _registeredMods[modName][version] =
                std::make_shared<Mod>(modName, version, type, source, folder);
        }

        void RegisterMod(const std::shared_ptr<Mod>& mod) {
            Log("Registering mod: {} {}", mod->GetName(), mod->GetVersion());
            _registeredMods[mod->GetName()][mod->GetVersion()] = mod;
        }

        // struct CInterface : public IModRegistry {

        // };

        // CInterface    _cInterface;
        // IModRegistry* GetCInterface() { return &_cInterface; }
    };
}
