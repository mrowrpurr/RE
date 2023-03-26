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
        void ReloadConfig() {
            Log("Reloading config...");
            FileSearchPaths::Load(_fileSearchPaths);
            auto configPath = _fileSearchPaths.Find(CONFIG_FILE_NAME);
            Log("Loading config from: {}", configPath);
        }

        //! Boot the Modding Framework runtime!
        void Boot() { ReloadConfig(); }

        IFileSearchPaths* GetFileSearchPaths() override { return &_fileSearchPaths; }
    };
}
