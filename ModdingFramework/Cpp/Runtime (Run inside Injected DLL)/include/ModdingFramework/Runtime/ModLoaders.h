#pragma once

#include <Logging.h>
#include <ModdingFramework/IModLoader.h>
#include <ModdingFramework/IModLoaders.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace ModdingFramework::Runtime {

    class ModLoaders {
    public:
        class CInterface : public IModLoaders {
            ModLoaders& _modLoaders;

        public:
            CInterface(ModLoaders& modLoaders) : _modLoaders(modLoaders) {}

            bool RegisterLoader(const char* type, IModLoader* loader) override {
                return _modLoaders.RegisterLoader(type, loader);
            }
            bool UnregisterLoader(const char* type) override {
                return _modLoaders.UnregisterLoader(type);
            }
            bool IsSupportedType(const char* type) override {
                return _modLoaders.IsSupportedType(type);
            }
            IModLoader* GetLoader(const char* type) override { return _modLoaders.GetLoader(type); }
            IModLoader* GetLoader(size_t index) override {
                return GetLoader(_modLoaders._loaderTypes[index]);
            }
            void         UnregisterAll() override { _modLoaders.UnregisterAll(); }
            size_t       GetLoaderCount() override { return _modLoaders.GetLoaderCount(); }
            const char** GetLoaderTypes() override { return _modLoaders._loaderTypes.data(); }
            bool LoadMod(IMod* mod) override { return GetLoader(mod->GetType())->LoadMod(mod); }
            bool UnloadMod(IMod* mod) override { return GetLoader(mod->GetType())->UnloadMod(mod); }
        };

    private:
        CInterface _interface = CInterface(*this);

        ModLoaders(const ModLoaders&)            = delete;
        ModLoaders(ModLoaders&&)                 = delete;
        ModLoaders& operator=(const ModLoaders&) = delete;
        ModLoaders& operator=(ModLoaders&&)      = delete;

        std::unordered_map<std::string, IModLoader*> _loaders;
        std::vector<const char*>                     _loaderTypes;

    public:
        ModLoaders()  = default;
        ~ModLoaders() = default;

        bool IsSupportedType(const std::string& type) {
            return _loaders.find(type) != _loaders.end();
        }
        bool RegisterLoader(const std::string& type, IModLoader* loader) {
            if (IsSupportedType(type)) {
                Log("ModLoaders", "Loader for type '{}' already registered", type);
                return false;
            }
            _loaders[type] = loader;
            _loaderTypes.push_back(type.c_str());
            return true;
        }
        bool UnregisterLoader(const std::string& type) {
            if (!IsSupportedType(type)) {
                Log("ModLoaders", "Loader for type '{}' not registered", type);
                return false;
            }
            _loaders.erase(type);
            return true;
        }

        IModLoader* GetLoader(const std::string& type) {
            if (!IsSupportedType(type)) {
                Log("ModLoaders", "Loader for type '{}' not registered", type);
                return nullptr;
            }
            return _loaders[type];
        }
        IModLoader* GetLoader(size_t index) {
            if (index >= _loaderTypes.size()) {
                Log("ModLoaders", "Loader index '{}' out of bounds", index);
                return nullptr;
            }
            return _loaders[_loaderTypes[index]];
        }
        void UnregisterAll() {
            _loaders.clear();
            _loaderTypes.clear();
        }
        size_t                          GetLoaderCount() { return _loaders.size(); }
        const std::vector<const char*>& GetLoaderTypes() { return _loaderTypes; }
        bool                            LoadMod(IMod* mod) {
            if (!mod) {
                Log("LoadMod: Mod pointer is null");
                return false;
            }
            if (!IsSupportedType(mod->GetType())) {
                Log("LoadMod: Mod type '{}' not supported", mod->GetType());
                return false;
            }
            return GetLoader(mod->GetType())->LoadMod(mod);
        }
        bool UnloadMod(IMod* mod) {
            if (!mod) {
                Log("UnloadMod: Mod pointer is null");
                return false;
            }
            if (!IsSupportedType(mod->GetType())) {
                Log("UnloadMod: Mod type '{}' not supported", mod->GetType());
                return false;
            }
            return GetLoader(mod->GetType())->UnloadMod(mod);
        }

        CInterface* GetCInterface() { return &_interface; }
    };
}
