#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "StatefulApp/State.h"
#include "StatefulApp/Variables.h"

namespace StatefulApp {

    class App;

    class StateMachine {
        std::unordered_map<std::string, std::shared_ptr<State>> _states;
        std::string                                             _currentState = "";
        std::shared_ptr<Variables>                              _variables;

    public:
        StateMachine(std::shared_ptr<Variables> variables) : _variables(std::move(variables)) {}

        void AddState(const std::string& name) {
            if (_states.contains(name))
                throw std::runtime_error("State with name '" + name + "' already exists");
            _states[name] = std::make_shared<State>(name);
        }
        std::shared_ptr<State> GetState(const std::string& name) const { return _states.at(name); }

        void        SetCurrentState(const std::string& stateName) { _currentState = stateName; }
        std::string GetCurrentState() const { return _currentState; }

        void PerformStateActions(const std::string& stateName) {
            GetState(stateName)->PerformActions(_variables);
        }

        void GotoState(const std::string& stateName) {
            SetCurrentState(stateName);
            PerformStateActions(stateName);
        }

        std::vector<std::string> GetStateNames() const {
            std::vector<std::string> stateNames;
            for (auto& [name, state] : _states) stateNames.push_back(name);
            return stateNames;
        }
    };
}
