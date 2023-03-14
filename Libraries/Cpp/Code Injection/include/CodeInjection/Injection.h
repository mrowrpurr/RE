#pragma once

#include <StringFormatting.h>

#include <any>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "Actions.h"
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
         * States
         */

        Injection& On(const std::string& stateName, std::function<void(Injection&)> block) {
            _currentlyConfiguringState = FindOrCreateState(stateName);
            block(*this);
            _currentlyConfiguringState = nullptr;
            return *this;
        }
        Injection& Install(std::function<void(Injection&)> block) { return On("Install", block); }
        Injection& Uninstall(std::function<void(Injection&)> block) {
            return On("Uninstall", block);
        }
        Injection& Configure(std::function<void(Injection&)> block) {
            return On("Configure", block);
            Goto("Configure");  // <--- Configure() actions are run immediately
        }
        void Goto(const std::string& stateName) {
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
            auto found = _variables.find(name);
            if (found == _variables.end())
                throw std::runtime_error(string_format("Variable {} not found", name));
            return std::any_cast<T&>(found->second);
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
    };
}
