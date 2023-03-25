#pragma once

#include <Serialization.h>

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

        std::filesystem::path GetModsFolder() {
            return "Data Files/Modding/Mods";

            // TODO!

            Log("The current working directory is: {}", std::filesystem::current_path().string());

            auto iniFileName = "modding_framework.ini";
            if (!std::filesystem::exists(iniFileName)) {
                iniFileName = "Data/modding_framework.ini";
            }

            if (!std::filesystem::exists(iniFileName)) {
                Log("INI file '{}' does not exist, exiting...", iniFileName);
                return {};
            }

            // TODO - don't read this all the time right here so lazily...
            auto config     = Serialization::LoadFile("modding_framework.ini")["Modding Framework"];
            auto modsFolder = config.Get("mods");
            Log("Mods folder is: {}", modsFolder);
            return modsFolder;
        }
    };
}
