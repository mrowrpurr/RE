#pragma once

#include <Logging.h>
#include <Serialization.h>

#include <memory>
#include <string>

#include "ModdingFramework/IMod.h"


namespace ModdingFramework::Runtime {

    class Mod : public IMod {
        Mod(const Mod&)            = delete;
        Mod(Mod&&)                 = delete;
        Mod& operator=(const Mod&) = delete;
        Mod& operator=(Mod&&)      = delete;

        std::string _name;
        std::string _version;
        std::string _type;
        std::string _source;
        std::string _folder;
        bool        _loaded = true;

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
        bool        Load() override { return _loaded = true; }
        bool        Unload() override { return _loaded = false; }

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
