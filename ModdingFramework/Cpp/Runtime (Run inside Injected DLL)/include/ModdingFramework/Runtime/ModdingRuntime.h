#pragma once

#include <Logging.h>
#include <ModdingFramework\IModdingRuntime.h>

#include "FileSearchPaths.h"
#include "RuntimeConfig.h"

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
        RuntimeConfig   _runtimeConfig;

        // ModManager --> (ModLoader + ModRegistry)
        // FileSearchPaths

    public:
        static ModdingRuntime& GetRuntime() {
            static ModdingRuntime runtime;
            return runtime;
        }

        //! Load modding_framework.ini
        void ReloadConfig() {
            FileSearchPaths::Reload(_fileSearchPaths);
            auto configPath = _fileSearchPaths.Find(CONFIG_FILE_NAME);
            if (configPath.empty()) {
                Log("Could not find Modding Framework config file: {}", CONFIG_FILE_NAME);
                return;
            }
            RuntimeConfig::Load(_runtimeConfig, configPath);
        }

        //! Boot the Modding Framework runtime!
        void Boot() { ReloadConfig(); }

        IRuntimeConfig*   GetRuntimeConfig() override { return &_runtimeConfig; }
        IFileSearchPaths* GetFileSearchPaths() override { return &_fileSearchPaths; }
    };
}
