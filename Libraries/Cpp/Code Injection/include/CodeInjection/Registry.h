#pragma once

#include <CodeInjection/Injection.h>
#include <string_format.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace CodeInjection {

    class Registry {
        std::unordered_map<std::string, std::shared_ptr<Injection>> _injections;

        Registry()                           = default;
        ~Registry()                          = default;
        Registry(const Registry&)            = delete;
        Registry(Registry&&)                 = delete;
        Registry& operator=(const Registry&) = delete;
        Registry& operator=(Registry&&)      = delete;

    public:
        static Registry& GetSingleton() {
            static Registry singleton;
            return singleton;
        }

        std::shared_ptr<Injection> Register(const std::string& name) {
            if (_injections.contains(name))
                throw std::runtime_error(
                    string_format("Injection with name '{}' already exists", name)
                );
            _injections[name] = std::make_shared<Injection>(name);
        }

        std::shared_ptr<Injection> Get(const std::string& name) { return _injections[name]; }
    };
}
