#pragma once

#include <Logging.h>

#include <filesystem>

#include "ModINI.h"
#include "System.h"

namespace ModdingFramework::Runtime {

    // XXX - This is a hardcoded implementation of a mod discoverer for .dll native mods

    // TODO - rename to IModDiscoverer
    // TODO - make this abstract and have multiple implementations
    class ModDiscoverer {
    public:
        void DiscoverMods(System& system) {
            // TODO - implement
            Log("ModDiscoverer instance is discovering mods");

            // Get the folder with the .dll mods (each having a required .ini)
            auto modsFolder = system.GetModsFolder();

            Log("The current working directory is: {}", std::filesystem::current_path().string());
            auto absoluteModsFolder = std::filesystem::absolute(modsFolder);

            // Logging every file path, recursively, in the current working directory
            // for (auto& entry :
            //      std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
            //      {
            //     Log("-> {}", entry.path().string());
            // }

            // Return if the folder doesn't exist
            if (!std::filesystem::exists(absoluteModsFolder)) {
                Log("Mods folder doesn't exist: {}", absoluteModsFolder.string());
                return;
            }

            Log("Searching for .ini files in mods folder: {}", absoluteModsFolder.string());

            // Search recursively for .ini files in the modsFolder
            for (auto& entry : std::filesystem::recursive_directory_iterator(absoluteModsFolder)) {
                if (entry.path().extension() == ".ini") {
                    Log("Found mod ini file: {}", entry.path().string());
                    auto mod = ModFromINI(entry.path());
                    system.GetRegistry().RegisterMod(mod);
                }
            }
        }
    };
}
