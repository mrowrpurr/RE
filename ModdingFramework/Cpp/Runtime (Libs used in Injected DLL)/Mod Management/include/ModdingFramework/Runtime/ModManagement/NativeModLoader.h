#pragma once

#include <Logging.h>
#include <ModdingFramework/Runtime/Core/Mod.h>

namespace ModdingFramework::Runtime::ModManagement::NativeModLoader {
    void Load(const Core::Mod& mod) { Log("Loading native mod: {}", mod.GetName()); }
    void Unload(const Core::Mod& mod) { Log("Unloading native mod: {}", mod.GetName()); }
    bool IsLoaded(const Core::Mod& mod) { return false; }
}