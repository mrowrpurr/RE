#pragma once

#include <any>
#include <string>
#include <unordered_map>

namespace StatefulApp {

    class Variables {
        std::unordered_map<std::string, std::any> _variables;

    public:
        void SetVariable(const std::string& name, std::any value) { _variables[name] = value; }
        void Variable(const std::string& name, std::any value) { SetVariable(name, value); }
        void Var(const std::string& name, std::any value) { SetVariable(name, value); }
        template <typename T>
        void SetVariable(const std::string& name, T value) {
            _variables[name] = value;
        }
        template <typename T>
        void Variable(const std::string& name, T value) {
            SetVariable(name, value);
        }
        template <typename T>
        void Var(const std::string& name, T value) {
            SetVariable(name, value);
        }
        template <typename T>
        void Set(const std::string& name, T value) {
            SetVariable(name, value);
        }

        bool HasVariable(const std::string& name) const { return _variables.contains(name); }

        std::any GetVariable(const std::string& name) const { return _variables.at(name); }
        std::any Variable(const std::string& name) const { return GetVariable(name); }
        std::any Var(const std::string& name) const { return GetVariable(name); }
        template <typename T>
        T GetVariable(const std::string& name) const {
            return std::any_cast<T>(GetVariable(name));
        }
        template <typename T>
        T Variable(const std::string& name) const {
            return GetVariable<T>(name);
        }
        template <typename T>
        T Var(const std::string& name) const {
            return GetVariable<T>(name);
        }
        template <typename T>
        T Get(const std::string& name) const {
            return GetVariable<T>(name);
        }
    };
}
