#pragma once

#include <ModdingFramework/Runtime/ModManagement/ModRegistry.h>

#include <filesystem>
#include <string>

namespace ModdingFramework::Runtime {

    class System {
        ModManagement::ModRegistry _registry;

    public:
        static System& GetSystem() {
            static System instance;
            return instance;
        }

        ModManagement::ModRegistry& GetRegistry() { return _registry; }

        // TODO - make this a path
        std::filesystem::path GetModsFolder() const { return "Modding/Mods"; }
    };
}
