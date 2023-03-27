#pragma once

#include <Logging.h>
#include <Serialization.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "ModdingFramework/IMod.h"

namespace ModdingFramework::Runtime {

    class Mod : public IMod {
        Mod(const Mod&)            = delete;
        Mod(Mod&&)                 = delete;
        Mod& operator=(const Mod&) = delete;
        Mod& operator=(Mod&&)      = delete;

        std::string                             _name;
        std::string                             _version;
        std::string                             _type;
        std::string                             _source;
        std::string                             _folder;
        bool                                    _loaded = false;
        std::unordered_map<std::string, void*>  _data;
        std::unordered_map<std::string, size_t> _dataSizes;
        std::vector<std::string>                _dataKeys;

    public:
        Mod() = default;
        Mod(const std::string& name, const std::string& version, const std::string& type,
            const std::string& source, const std::string& folder)
            : _name(name), _version(version), _type(type), _source(source), _folder(folder) {}
        ~Mod() = default;

        const char* GetName() const override { return _name.c_str(); }
        const char* GetVersion() const override { return _version.c_str(); }
        const char* GetFolder() const override { return _folder.c_str(); }
        const char* GetType() const override { return _type.c_str(); }
        const char* GetSource() const override { return _source.c_str(); }
        bool        IsLoaded() const override { return _loaded; }

        // TODO - make this NOT available on the C interface, please :)
        void SetLoaded(bool loaded = true) override { _loaded = loaded; }

        void SetName(const std::string& name) { _name = name; }
        void SetVersion(const std::string& version) { _version = version; }
        void SetFolder(const std::string& folder) { _folder = folder; }
        void SetType(const std::string& type) { _type = type; }
        void SetSource(const std::string& source) { _source = source; }

        void SetData(const char* key, void* data, size_t size) override {
            _data[key]      = data;
            _dataSizes[key] = size;
            _dataKeys.push_back(key);
        }
        void*  GetData(const char* key) override { return _data[key]; }
        size_t GetDataSize(const char* key) override { return _dataSizes[key]; }
        size_t GetDataCount() override { return _data.size(); }
        void   ClearData() override {
            _data.clear();
            _dataSizes.clear();
            _dataKeys.clear();
        }
        const char** GetDataKeys() override {
            return reinterpret_cast<const char**>(_dataKeys.data());
        }
        bool HasDataKey(const char* key) override { return _data.find(key) != _data.end(); }
        void RemoveDataKey(const char* key) override {
            _data.erase(key);
            _dataSizes.erase(key);
            _dataKeys.erase(std::remove(_dataKeys.begin(), _dataKeys.end(), key), _dataKeys.end());
        }

        // TODO - move this into something else which can be responsible for loading Mod from
        // configs/etc
        static std::shared_ptr<Mod> FromINI(const std::string& iniPath) {
            auto mod = std::make_shared<Mod>();
            if (!std::filesystem::exists(iniPath)) {
                Log("File does not exist: {}", iniPath);
                return mod;
            }
            auto config     = Serialization::LoadFile(iniPath);
            auto modSection = config["Mod"];
            mod->_name      = modSection.Get("name");
            mod->_version   = modSection.Get("version");
            mod->_type      = modSection.Get("type");
            mod->_source    = modSection.Get("source");
            return mod;
        }
    };
}
