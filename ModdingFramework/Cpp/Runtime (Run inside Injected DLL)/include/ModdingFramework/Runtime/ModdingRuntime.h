#pragma once

#include <Logging.h>
#include <ModdingFramework\IModdingRuntime.h>

#include <filesystem>

#include "FileSearchPaths.h"
#include "ModLoaders.h"
#include "ModRegistry.h"
#include "NativeModLoader.h"
#include "RuntimeConfig.h"

namespace ModdingFramework::Runtime {

    constexpr auto CONFIG_FILE_NAME = "modding_framework.ini";

    class ModdingRuntime {
    public:
        class CInterface : public IModdingRuntime {
            ModdingRuntime& _runtime;

        public:
            CInterface(ModdingRuntime& runtime) : _runtime(runtime) {}

            IFileSearchPaths* GetFileSearchPaths() override {
                return _runtime.GetFileSearchPaths().GetCInterface();
            }
            IRuntimeConfig* GetRuntimeConfig() override {
                return _runtime.GetRuntimeConfig().GetCInterface();
            }
            IModRegistry* GetRegistry() override { return _runtime.GetRegistry().GetCInterface(); }
            IModLoaders*  GetModLoaders() override {
                return _runtime.GetModLoaders().GetCInterface();
            }
        };

    private:
        CInterface _cInterface{*this};

        ModdingRuntime()                                 = default;
        ~ModdingRuntime()                                = default;
        ModdingRuntime(const ModdingRuntime&)            = delete;
        ModdingRuntime(ModdingRuntime&&)                 = delete;
        ModdingRuntime& operator=(const ModdingRuntime&) = delete;
        ModdingRuntime& operator=(ModdingRuntime&&)      = delete;

        FileSearchPaths _fileSearchPaths;
        RuntimeConfig   _runtimeConfig;
        ModRegistry     _modRegistry;
        ModLoaders      _modLoaders;
        NativeModLoader _nativeModLoader{&_cInterface};

    public:
        static ModdingRuntime& GetRuntime() {
            static ModdingRuntime runtime;
            return runtime;
        }

        void ReloadConfig() {
            FileSearchPaths::Reload(_fileSearchPaths);
            auto configPath = _fileSearchPaths.Find(CONFIG_FILE_NAME);
            if (configPath.empty()) {
                Log("Could not find Modding Framework config file: {}", CONFIG_FILE_NAME);
                return;
            }
            RuntimeConfig::Load(_runtimeConfig, configPath);
        }

        void DiscoverMods() {
            auto modsPath = _fileSearchPaths.Find(_runtimeConfig.GetModsFolderPath());

            if (!std::filesystem::exists(modsPath)) {
                Log("Could not find mods folder: {}", modsPath);
                return;
            }

            for (const auto& entry : std::filesystem::recursive_directory_iterator(modsPath)) {
                if (entry.is_directory()) continue;
                if (entry.path().extension() != ".ini") continue;

                auto mod = Mod::FromINI(entry.path().string());
                mod->SetFolder(entry.path().parent_path().string());
                if (mod == nullptr) continue;

                _modRegistry.RegisterMod(mod);
            }
        }

        void Boot() {
            ReloadConfig();
            DiscoverMods();
            _modLoaders.RegisterLoader("native", &_nativeModLoader);
        }

        FileSearchPaths& GetFileSearchPaths() { return _fileSearchPaths; }
        RuntimeConfig&   GetRuntimeConfig() { return _runtimeConfig; }
        ModRegistry&     GetRegistry() { return _modRegistry; }
        ModLoaders&      GetModLoaders() { return _modLoaders; }

        IModdingRuntime* GetCInterface() { return &_cInterface; }
    };
}
