#pragma once

#include <memory>
#include <string>
#include <vector>

#include "InjectionAction.h"
#include "InjectionVariables.h"

namespace CodeInjection {

    class InjectionState {
        std::string                                   _name;
        std::shared_ptr<InjectionVariables>           _variables;
        std::vector<std::shared_ptr<InjectionAction>> _actions;

    public:
        InjectionState(const std::string& name, std::shared_ptr<InjectionVariables> variables)
            : _name(name), _variables(variables) {}

        std::string GetName() const { return _name; }

        void AddAction(std::shared_ptr<InjectionAction> action) { _actions.push_back(action); }

        void PerformActions() {
            // for (auto action : _actions) action->Perform(_variables);
        }
    };
}
