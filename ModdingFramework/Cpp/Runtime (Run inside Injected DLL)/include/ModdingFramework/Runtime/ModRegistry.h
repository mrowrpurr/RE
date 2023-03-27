#pragma once

#include <Logging.h>
#include <ModdingFramework\IModRegistry.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "Mod.h"

namespace ModdingFramework::Runtime {

    class ModRegistry {
    public:
        class CInterface : public IModRegistry {
            ModRegistry& _registry;

        public:
            CInterface(ModRegistry& registry) : _registry(registry) {}

            void RegisterMod(
                const char* name, const char* version, const char* type, const char* source,
                const char* folder
            ) override {
                _registry.RegisterMod(std::make_shared<Mod>(name, version, type, source, folder));
            }

            void UnregisterMod(const char* name, const char* version) override {
                _registry.UnregisterMod(name, version);
            }

            void UnregisterAllMods() override { _registry.UnregisterAllMods(); }

            size_t GetModCount() const override { return _registry.GetModCount(); }

            IMod* GetMod(size_t index) const override { return _registry.GetMod(index).get(); }

            IMod* GetMod(const char* name) const override { return _registry.GetMod(name).get(); }

            IMod* GetMod(const char* name, const char* version) const override {
                return _registry.GetMod(name, version).get();
            }
        };

    private:
        CInterface _cInterface{*this};

        ModRegistry(const ModRegistry&)            = delete;
        ModRegistry(ModRegistry&&)                 = delete;
        ModRegistry& operator=(const ModRegistry&) = delete;
        ModRegistry& operator=(ModRegistry&&)      = delete;

        std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<Mod>>>
            _registeredMods;

    public:
        ModRegistry()  = default;
        ~ModRegistry() = default;

        void RegisterMod(const std::shared_ptr<Mod>& mod) {
            Log("Registering mod: {} {}", mod->GetName(), mod->GetVersion());
            _registeredMods[mod->GetName()][mod->GetVersion()] = mod;
        }

        void UnregisterMod(const std::string& name, const std::string& version) {
            Log("Unregistering mod: {} {}", name, version);
            _registeredMods[name].erase(version);
        }

        void UnregisterAllMods() {
            Log("Unregistering all mods");
            _registeredMods.clear();
        }

        size_t GetModCount() const { return _registeredMods.size(); }

        std::shared_ptr<Mod> GetMod(size_t index) const {
            auto it = _registeredMods.begin();
            std::advance(it, index);
            return it->second.begin()->second;
        }

        std::shared_ptr<Mod> GetMod(const std::string& name) const {
            return _registeredMods.at(name).begin()->second;
        }

        std::shared_ptr<Mod> GetMod(const std::string& name, const std::string& version) const {
            return _registeredMods.at(name).at(version);
        }

        void ForEachMod(const std::function<void(const std::shared_ptr<Mod>&)>& callback) const {
            for (const auto& [name, versions] : _registeredMods)
                for (const auto& [version, mod] : versions) callback(mod);
        }

        IModRegistry* GetCInterface() { return &_cInterface; }
    };
}
