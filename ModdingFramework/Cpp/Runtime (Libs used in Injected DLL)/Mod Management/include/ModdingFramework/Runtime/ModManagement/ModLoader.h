#pragma once

#include <Logging.h>
#include <ModdingFramework/Runtime/Core/Mod.h>

#include "NativeModLoader.h"

namespace ModdingFramework::Runtime::ModManagement {
    class ModLoader {
    public:
        void Load(const Core::Mod& mod) {
            Log("Loading mod: {}", mod.GetName());
            if (mod.GetType() == "native") NativeModLoader::Load(mod);
            else Log("Unknown mod type: {}", mod.GetType());
        }
        void Unload(const Core::Mod& mod) {
            Log("Unloading mod: {}", mod.GetName());
            if (mod.GetType() == "native") NativeModLoader::Unload(mod);
            else Log("Unknown mod type: {}", mod.GetType());
        }
        bool IsLoaded(const Core::Mod& mod) {
            if (mod.GetType() == "native") return NativeModLoader::IsLoaded(mod);
            else Log("Unknown mod type: {}", mod.GetType());
            return false;
        }
    };
}