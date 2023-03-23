#pragma once

#include <Logging.h>

#include <string>
#include <unordered_map>

#include "Mod.h"
#include "NativeModLoader.h"

namespace ModdingFramework::Runtime {

    class ModLoader {
        std::unordered_map<std::string, std::unordered_map<std::string, bool>> _modLoadedStates;

        void SetModLoadedState(const Mod& mod, bool loaded) {
            _modLoadedStates[std::string{mod.GetName()}][std::string{mod.GetVersion()}] = loaded;
        }

        ModLoader(const ModLoader&)            = delete;
        ModLoader(ModLoader&&)                 = delete;
        ModLoader& operator=(const ModLoader&) = delete;
        ModLoader& operator=(ModLoader&&)      = delete;

    public:
        ModLoader()  = default;
        ~ModLoader() = default;

        void Load(const Mod& mod) {
            Log("Loading mod: {}", mod.GetName());
            if (mod.GetType() == "native") {
                if (NativeModLoader::Load(mod)) SetModLoadedState(mod, true);
                else Log("Failed to load native mod: {}", mod.GetName());
            } else Log("Unknown mod type: {}", mod.GetType());
        }
        void Unload(const Mod& mod) {
            Log("Unloading mod: {}", mod.GetName());
            if (mod.GetType() == "native") {
                if (NativeModLoader::Unload(mod)) SetModLoadedState(mod, false);
                else Log("Failed to unload native mod: {}", mod.GetName());
            } else Log("Unknown mod type: {}", mod.GetType());
        }
        bool IsLoaded(const Mod& mod) {
            Log("Checking if mod is loaded: {}", mod.GetName());
            if (mod.GetType() == "native") {
                auto found = _modLoadedStates.find(mod.GetName());
                if (found == _modLoadedStates.end()) return false;
                auto foundVersion = found->second.find(mod.GetVersion());
                if (foundVersion == found->second.end()) return false;
                return foundVersion->second;
            } else {
                Log("Unknown mod type: {}", mod.GetType());
                return false;
            }
        }
    };
}