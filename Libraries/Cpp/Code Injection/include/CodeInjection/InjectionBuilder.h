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

        InjectionBuilder& ReadBytes(Actions::ReadBytesActionParams actionParams) {
            AddAction(Actions::ReadBytesAction(actionParams));
            return *this;
        }

        InjectionBuilder& WriteBytes(Actions::WriteBytesActionParams actionParams) {
            AddAction(Actions::WriteBytesAction(actionParams));
            return *this;
        }

        InjectionBuilder& AllocateMemory(Actions::AllocateMemoryActionParams actionParams) {
            AddAction(Actions::AllocateMemoryAction(actionParams));
            return *this;
        }

        InjectionBuilder& DeallocateMemory(Actions::DeallocateMemoryActionParams actionParams) {
            AddAction(Actions::DeallocateMemoryAction(actionParams));
            return *this;
        }

        template <typename T>
        InjectionBuilder& Var(const std::string& name, T value) {
            _variables->Var(name, value);
            return *this;
        }

        template <typename T>
        T& Var(const std::string& name) {
            return _variables->Var<T>(name);
        }
    };
}