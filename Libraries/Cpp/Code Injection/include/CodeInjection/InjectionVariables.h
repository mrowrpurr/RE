#pragma once

#include <any>
#include <string>
#include <unordered_map>

namespace CodeInjection {

    int NEXT_VARS_ID = 1;

    class InjectionVariables {
        int                                       id = NEXT_VARS_ID++;
        std::unordered_map<std::string, std::any> _variables;

    public:
        template <typename T>
        T& Set(const std::string& name, T defaultValue) {
            if (!_variables.contains(name)) {
                _variables[name] = defaultValue;
            }
            return std::any_cast<T&>(_variables[name]);
        }

        template <typename T>
        T& Get(const std::string& name) {
            return std::any_cast<T&>(_variables[name]);
        }
    };
}
