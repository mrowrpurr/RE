#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "CodeInjecting/CodeInjection.h"

namespace CodeInjecting {
    class Registry {
        std::unordered_map<std::string, std::shared_ptr<CodeInjection>> _injections;

        Registry()                           = default;
        ~Registry()                          = default;
        Registry(const Registry&)            = delete;
        Registry(Registry&&)                 = delete;
        Registry& operator=(const Registry&) = delete;
        Registry& operator=(Registry&&)      = delete;

    public:
        static Registry& GetRegistry() {
            static Registry singleton;
            return singleton;
        }

        void Register(const std::string& name, std::shared_ptr<CodeInjection> injection) {
            if (_injections.contains(name))
                throw std::runtime_error("Injection with name '" + name + "' already exists");
            _injections[name] = injection;
        }

        std::shared_ptr<CodeInjection> Get(const std::string& name) { return _injections[name]; }
        std::shared_ptr<CodeInjection> operator[](const std::string& name) { return Get(name); }
    };
}
