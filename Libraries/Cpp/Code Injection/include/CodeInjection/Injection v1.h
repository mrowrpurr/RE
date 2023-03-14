#pragma once

#include <any>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "Actions.h"

namespace CodeInjection {

    class Injection {
    public:
        Injection(const std::string& name)
            : _name(name), _variables(std::make_shared<InjectionVariables>()) {}

        const std::string& GetName() const { return _name; }

        /**
         * States
         */

        /**
         * Variables
         */

        template <typename T>
        Injection& Var(const std::string& name, T value) {
            _variables->Var(name, value);
            return *this;
        }
        template <typename T>
        T& Var(const std::string& name) {
            return _variables->Var<T>(name);
        }

        /**
         * Actions
         */

        template <typename T>
        Injection& AddAction(T action) {
            if (_currentlyConfiguringState)
                _currentlyConfiguringState->AddAction(std::make_shared<T>(action));
            return *this;
        }

        Injection& ReadBytes(Actions::ReadBytesActionParams params) {
            return AddAction(Actions::ReadBytesAction(params));
        }

        Injection& WriteBytes(Actions::WriteBytesActionParams params) {
            return AddAction(Actions::WriteBytesAction(params));
        }

        Injection& AllocateMemory(Actions::AllocateMemoryActionParams params) {
            return AddAction(Actions::AllocateMemoryAction(params));
            return *this;
        }
    };
}
