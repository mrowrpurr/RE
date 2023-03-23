#pragma once

#include <Logging.h>
#include <ModdingFramework/Runtime/ModManagement/ModINI.h>
#include <ModdingFramework/Runtime/System.h>

#include <filesystem>

namespace ModdingFramework::Runtime::ModManagement {

    // XXX - This is a hardcoded implementation of a mod discoverer for .dll native mods

    // TODO - rename to IModDiscoverer
    // TODO - make this abstract and have multiple implementations
    class ModDiscoverer {
    public:
        void DiscoverMods(System& system) {
            // TODO - implement
            Log("ModDiscoverer instance is fiscovering mods");

            // Get the folder with the .dll mods (each having a required .ini)
            auto modsFolder = system.GetModsFolder();

            // Return if the folder doesn't exist
            if (!std::filesystem::exists(modsFolder)) {
                Log("Mods folder doesn't exist: {}", modsFolder.string());
                return;
            }

            // Search recursively for .ini files in the modsFolder
            for (auto& entry : std::filesystem::recursive_directory_iterator(modsFolder)) {
                if (entry.path().extension() == ".ini") {
                    Log("Found mod ini file: {}", entry.path().string());
                    auto mod = ModFromINI(entry.path());
                    system.GetRegistry().RegisterMod(mod);
                }
            }
        }
    };
}
