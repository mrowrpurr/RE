#pragma once

#include <string>

namespace Hooks {

    // Represents a hook to a specific address implemented via a JMP
    class Hook {
        std::string _name;
        bool        _installed = false;

    public:
        const std::string& GetName() const { return _name; }
        Hook&              SetName(const std::string& name) {
            _name = name;
            return *this;
        }

        void Install() {}
        void Uninstall() {}
        bool Toggle() { return true; }
    };
}
