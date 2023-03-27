#pragma once

#include <Logging.h>
#include <ModdingFramework\IModdingRuntime.h>

#include <filesystem>

#include "FileSearchPaths.h"
#include "ModRegistry.h"
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
        ModRegistry     _modRegistry;

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

        //! Do this inline and extract to something with the responsibility of handling this soon
        void DiscoverMods() {
            // For now, just look for all mods in the mods folder
            auto modsPath = _fileSearchPaths.Find(_runtimeConfig.GetModsFolderPath());

            if (!std::filesystem::exists(modsPath)) {
                Log("Could not find mods folder: {}", modsPath);
                return;
            }

            for (const auto& entry : std::filesystem::recursive_directory_iterator(modsPath)) {
                if (entry.is_directory()) continue;
                if (entry.path().extension() != ".ini") continue;

                auto mod = Mod::FromINI(entry.path().string());
                if (mod == nullptr) continue;

                _modRegistry.RegisterMod(mod);
            }
        }

        void Boot() {
            ReloadConfig();
            DiscoverMods();
        }

        IRuntimeConfig*   GetRuntimeConfig() override { return &_runtimeConfig; }
        IFileSearchPaths* GetFileSearchPaths() override { return &_fileSearchPaths; }
    };
}
