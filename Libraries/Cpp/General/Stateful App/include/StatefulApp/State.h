#pragma once

#include <memory>
#include <vector>

#include "StatefulApp/Action.h"
#include "StatefulApp/Variables.h"

namespace StatefulApp {

    class App;

    class State {
        std::string                          _name;
        std::vector<std::shared_ptr<Action>> _actions;

    public:
        explicit State(const std::string& name) : _name(name) {}

        const std::string& GetName() const { return _name; }

        template <typename T>
        void AddAction(T action) {
            _actions.push_back(std::make_shared<T>(action));
        }

        void PerformActions(std::shared_ptr<Variables> variables) {
            for (auto& action : _actions) action->Perform(variables);
        }
    };
}