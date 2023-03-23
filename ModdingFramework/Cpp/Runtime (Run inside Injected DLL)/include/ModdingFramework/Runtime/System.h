#pragma once

#include <filesystem>
#include <string>

#include "ModLoader.h"
#include "ModRegistry.h"

namespace ModdingFramework::Runtime {

    class System {
        ModRegistry _registry;
        ModLoader   _loader;

    public:
        static System& GetSystem() {
            static System instance;
            return instance;
        }

        ModRegistry& GetRegistry() { return _registry; }
        ModLoader&   GetLoader() { return _loader; }

        // TODO - read from config
        std::filesystem::path GetModsFolder() const { return "Modding/Mods"; }
    };
}
