#pragma once

#include <any>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "InjectionState.h"

namespace CodeInjection {

    class Injection {
        std::string                                                      _name;
        std::unordered_map<std::string, std::any>                        _variables;
        std::unordered_map<std::string, std::shared_ptr<InjectionState>> _states;
        std::shared_ptr<InjectionState>                                  _currentState;
        std::shared_ptr<InjectionState>                                  _currentlyConfiguringState;

        std::shared_ptr<InjectionState> GetStateIfExists(std::string name) {
            if (_states.contains(name)) return _states[name];
            return nullptr;
        }
        std::shared_ptr<InjectionState> FindOrCreateState(const std::string& name) {
            if (_states.contains(name)) return _states[name];
            auto state    = std::make_shared<InjectionState>(name, *this);
            _states[name] = state;
            return state;
        }

    public:
        Injection(const std::string& name) : _name(name) {}

        std::string_view GetName() const { return _name; }

        /**
         * Configure block (just for semantics)
         */

        Injection& Configure(std::function<void(Injection&)> block) {
            block(*this);
            return *this;
        }

        /**
         * States
         */

        Injection& On(const std::string& stateName) {
            _currentlyConfiguringState = FindOrCreateState(stateName);
            return *this;
        }
        Injection& OnInstall() { return On("Install"); }
        Injection& OnUninstall() { return On("Uninstall"); }
        void       Goto(const std::string& stateName) {
            auto state = GetStateIfExists(stateName);
            if (state) state->PerformActions();
        }
        void Install() { Goto("Install"); }
        void Uninstall() { Goto("Uninstall"); }

        /**
         * Variables
         */

        template <typename T>
        Injection& Var(const std::string& name, T value) {
            _variables[name] = value;
            return *this;
        }
        template <typename T>
        T& Var(const std::string& name) {
            return std::any_cast<T&>(_variables[name]);
        }
    };
}
