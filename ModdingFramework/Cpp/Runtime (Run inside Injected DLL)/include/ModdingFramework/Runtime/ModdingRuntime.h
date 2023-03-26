#pragma once

#include <ModdingFramework\IModdingRuntime.h>
#include <Serialization.h>

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
            FileSearchPaths::LoadFromEnvironmentVariable(_fileSearchPaths);
            ReloadConfig();
        }

        IFileSearchPaths* GetFileSearchPaths() override { return &_fileSearchPaths; }
    };
}
