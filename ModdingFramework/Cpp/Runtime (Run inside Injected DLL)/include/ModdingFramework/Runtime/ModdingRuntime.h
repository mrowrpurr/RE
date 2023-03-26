#pragma once

#include <Logging.h>
// #include <SimpleIni.h>  // <----

// ^ Require this first, because stupid.

#include <ModdingFramework\IModdingRuntime.h>
#include <Serialization.h>

#include <filesystem>

#include "FileSearchPaths.h"

namespace ModdingFramework::Runtime {

    constexpr auto CONFIG_FILE_NAME = "modding_framework.ini";

    class ModdingRuntime : public IModdingRuntime {
        ModdingRuntime()                                 = default;
        ~ModdingRuntime()                                = default;
        ModdingRuntime(const ModdingRuntime&)            = delete;
        ModdingRuntime(ModdingRuntime&&)                 = delete;
        ModdingRuntime& operator=(const ModdingRuntime&) = delete;
        ModdingRuntime& operator=(ModdingRuntime&&)      = delete;

        FileSearchPaths _fileSearchPaths;

        // Config
        // ModManager --> (ModLoader + ModRegistry)
        // FileSearchPaths

    public:
        static ModdingRuntime& GetRuntime() {
            static ModdingRuntime runtime;
            return runtime;
        }

        //! Load modding_framework.ini
        void ReloadConfig() { auto configPath = _fileSearchPaths.Find(CONFIG_FILE_NAME); }

        //! Boot the Modding Framework runtime!
        void Boot() {
            Log("Wassup y'all? That totally sucked, omg right?");

            auto moddingFrameworkIniPath = "Data Files/modding_framework.ini";

            if (!std::filesystem::exists(moddingFrameworkIniPath)) {
                Log("Modding Framework config file not found! ({})", moddingFrameworkIniPath);
                return;
            }

            auto moddingFrameworkIni = Serialization::LoadFile(moddingFrameworkIniPath);
            auto config              = moddingFrameworkIni["Modding Framework"];
            auto game                = config.Get("game");
            Log("Game: {}", game);

            // FileSearchPaths::LoadFromEnvironmentVariable(_fileSearchPaths);
            // ReloadConfig();

            // Use Serialization...
            // auto x = Serialization::LoadFile("butts.ini");
        }

        IFileSearchPaths* GetFileSearchPaths() override { return &_fileSearchPaths; }
    };
}
