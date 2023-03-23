#pragma once

#include <string>

namespace ModdingFramework::Runtime::Core {

    class Mod {
        std::string _name;
        std::string _version;
        std::string _type;
        std::string _source;

    public:
        // Mod() = default;
        Mod(const std::string& name, const std::string& version, const std::string& type,
            const std::string& source)
            : _name(name), _version(version), _type(type), _source(source) {}

        const std::string& GetName() const { return _name; }
        const std::string& GetVersion() const { return _version; }
        const std::string& GetType() const { return _type; }
        const std::string& GetSource() const { return _source; }
    };
}
