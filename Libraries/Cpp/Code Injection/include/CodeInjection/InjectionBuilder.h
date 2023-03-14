#pragma once

#include "Actions.h"
#include "InjectionAction.h"
#include "InjectionVariables.h"

namespace CodeInjection {

    class InjectionBuilder {
        std::shared_ptr<std::vector<std::shared_ptr<InjectionAction>>> _actions;
        std::shared_ptr<InjectionVariables>                            _variables;

    public:
        InjectionBuilder() = default;
        InjectionBuilder(
            std::shared_ptr<InjectionVariables>                            variables,
            std::shared_ptr<std::vector<std::shared_ptr<InjectionAction>>> actions
        )
            : _actions(actions), _variables(variables) {}

        template <typename T>
        InjectionBuilder& AddAction(T action) {
            _actions->push_back(std::make_shared<T>(action));
            return *this;
        }

        InjectionBuilder& AllocateMemory(Actions::AllocateMemoryActionParams actionParams) {
            AddAction(Actions::AllocateMemoryAction(actionParams));
            return *this;
        }
    };
}