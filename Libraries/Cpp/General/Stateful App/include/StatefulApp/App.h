#pragma once

#include <any>

#include "StatefulApp/Action.h"
#include "StatefulApp/StateMachine.h"
#include "StatefulApp/Variables.h"

namespace StatefulApp {

    class App {
        std::shared_ptr<Variables>    _variables;
        std::shared_ptr<StateMachine> _stateMachine;
        std::string                   _currentlyConfiguringState = "";

    public:
        App()
            : _variables(std::make_shared<Variables>()),
              _stateMachine(std::make_shared<StateMachine>(_variables)) {}

        /**
         * Variables
         */

        App& Variable(const std::string& name, std::any value) {
            _variables->Variable(name, std::move(value));
            return *this;
        }
        template <typename T>
        App& Variable(const std::string& name, T value) {
            _variables->Set(name, value);
            return *this;
        }
        App& Set(const std::string& name, std::any value) {
            _variables->Set(name, std::move(value));
            return *this;
        }
        template <typename T>
        App& Set(const std::string& name, T value) {
            _variables->Set(name, value);
            return *this;
        }

        /**
         * States
         */

        std::shared_ptr<State> GetState(const std::string& name) const {
            return _stateMachine->GetState(name);
        }
        App& SetState(const std::string& name) {
            _stateMachine->SetCurrentState(name);
            return *this;
        }
        App& AddState(const std::string& name) {
            _stateMachine->AddState(name);
            _currentlyConfiguringState = name;
            return *this;
        }
        App& On(const std::string& name) {
            if (!GetState(name)) return AddState(name);
            _currentlyConfiguringState = name;
            return *this;
        }
        App& GotoState(const std::string& name) {
            _stateMachine->GotoState(name);
            return *this;
        }
        App& Goto(const std::string& name) { return GotoState(name); }

        /**
         * Actions
         */

        template <typename T>
        App& AddAction(const std::string& name, T action) {
            GetState(name)->AddAction(std::move(action));
            return *this;
        }

        // template <typename T>
        // App& AddAction(T action) {
        //     GetState(_currentlyConfiguringState)->AddAction(std::move(action));
        //     return *this;
        // }
    };
}
