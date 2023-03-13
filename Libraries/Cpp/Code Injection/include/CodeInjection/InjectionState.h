#pragma once

#include <memory>
#include <string>
#include <vector>

#include "InjectionAction.h"

namespace CodeInjection {

    class Injection;

    class InjectionState {
        std::string                                   _name;
        Injection&                                    _injection;
        std::vector<std::shared_ptr<InjectionAction>> _actions;

    public:
        InjectionState(std::string name, Injection& injection)
            : _name(name), _injection(injection) {}

        std::string GetName() const { return _name; }

        void AddAction(std::shared_ptr<InjectionAction> action) { _actions.push_back(action); }

        void PerformActions() {
            for (auto action : _actions) action->Perform(_injection);
        }
    };
}
