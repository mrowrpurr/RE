#pragma once

#include <any>
#include <string>
#include <unordered_map>

namespace CodeInjection {

    class InjectionVariables {
        std::unordered_map<std::string, std::any> _variables;

    public:
        template <typename T>
        void Set(const std::string& name, T defaultValue) {
            _variables[name] = defaultValue;
        }

        template <typename T>
        T& Get(const std::string& name) {
            return std::any_cast<T&>(_variables[name]);
        }
    };
}
