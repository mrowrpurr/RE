#pragma once

#include <Logging.h>
#include <ModdingFramework/IRuntimeConfig.h>
#include <Serialization.h>

#include <filesystem>
#include <string>

namespace ModdingFramework::Runtime {

    class RuntimeConfig {
    public:
        class CInterface : public IRuntimeConfig {
            RuntimeConfig& _config;

        public:
            CInterface(RuntimeConfig& config) : _config(config) {}
            const char* GetGameExecutable() override { return _config.GetGameExecutable().c_str(); }
            const char* GetModsFolderPath() override { return _config.GetModsFolderPath().c_str(); }
        };

    private:
        CInterface _cInterface{*this};

        RuntimeConfig(const RuntimeConfig&)            = delete;
        RuntimeConfig(RuntimeConfig&&)                 = delete;
        RuntimeConfig& operator=(const RuntimeConfig&) = delete;
        RuntimeConfig& operator=(RuntimeConfig&&)      = delete;

        std::string _gameExecutable;
        std::string _modsFolderPath = "Modding/Mods";

    public:
        RuntimeConfig()  = default;
        ~RuntimeConfig() = default;

        void SetGameExecutable(const std::string& gameExecutable) {
            _gameExecutable = gameExecutable;
        }
        void SetModsFolderPath(const std::string& modsFolderPath) {
            _modsFolderPath = modsFolderPath;
        }

        const std::string& GetGameExecutable() const { return _gameExecutable; }
        const std::string& GetModsFolderPath() const { return _modsFolderPath; }

        static constexpr auto MODDING_FRAMEWORK_CONFIG_SECTION_NAME = "Modding Framework";
        static constexpr auto MODDING_FRAMEWORK_CONFIG_KEY_GAME     = "game";
        static constexpr auto MODDING_FRAMEWORK_CONFIG_KEY_MODS     = "mods";

        static void Load(RuntimeConfig& config, const std::string& configPath) {
            if (!std::filesystem::exists(configPath)) {
                Log("Could not load Modding Framework config file: {}", configPath);
                return;
            }
            auto loadedConfig = Serialization::LoadFile(configPath);
            if (!loadedConfig.HasKey(MODDING_FRAMEWORK_CONFIG_SECTION_NAME)) {
                Log("Could not find Modding Framework config section in: {}", configPath);
                return;
            }
            auto loadedModdingFrameworkConfig = loadedConfig[MODDING_FRAMEWORK_CONFIG_SECTION_NAME];
            if (loadedModdingFrameworkConfig.HasKey(MODDING_FRAMEWORK_CONFIG_KEY_GAME))
                config.SetGameExecutable(
                    loadedModdingFrameworkConfig.Get(MODDING_FRAMEWORK_CONFIG_KEY_GAME)
                );
            if (loadedModdingFrameworkConfig.HasKey(MODDING_FRAMEWORK_CONFIG_KEY_MODS))
                config.SetModsFolderPath(
                    loadedModdingFrameworkConfig.Get(MODDING_FRAMEWORK_CONFIG_KEY_MODS)
                );
        }

        IRuntimeConfig* GetCInterface() { return &_cInterface; }
    };
}
