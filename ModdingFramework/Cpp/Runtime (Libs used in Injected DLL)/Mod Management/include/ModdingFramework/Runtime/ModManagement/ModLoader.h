#pragma once

#include <Logging.h>
#include <ModdingFramework/Runtime/Core/Mod.h>

#include <string>
#include <unordered_map>

#include "NativeModLoader.h"

namespace ModdingFramework::Runtime::ModManagement {

    class ModLoader {
        std::unordered_map<std::string, std::unordered_map<std::string, bool>> _modLoadedStates;

        void SetModLoadedState(const Core::Mod& mod, bool loaded) {
            _modLoadedStates[std::string{mod.GetName()}][std::string{mod.GetVersion()}] = loaded;
        }

    public:
        ~ModLoader() = default;
        ModLoader() = default;

        void Load(const Core::Mod& mod) {
            Log("Loading mod: {}", mod.GetName());
            if (mod.GetType() == "native") {
                if (NativeModLoader::Load(mod)) SetModLoadedState(mod, true);
                else Log("Failed to load native mod: {}", mod.GetName());
            } else Log("Unknown mod type: {}", mod.GetType());
        }
        void Unload(const Core::Mod& mod) {
            Log("Unloading mod: {}", mod.GetName());
            if (mod.GetType() == "native") {
                if (NativeModLoader::Unload(mod)) SetModLoadedState(mod, false);
                else Log("Failed to unload native mod: {}", mod.GetName());
            } else Log("Unknown mod type: {}", mod.GetType());
        }
        bool IsLoaded(const Core::Mod& mod) {
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