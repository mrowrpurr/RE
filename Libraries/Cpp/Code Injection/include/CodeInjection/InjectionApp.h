#pragma once

#include <Logging.h>

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "InjectionBuilder.h"
#include "InjectionState.h"
#include "InjectionVariables.h"

namespace CodeInjection {

    class InjectionApp {
        std::string                                                      _name;
        bool                                                             _isInstalled = false;
        std::shared_ptr<InjectionVariables>                              _variables;
        std::unordered_map<std::string, std::shared_ptr<InjectionState>> _states;

        std::shared_ptr<InjectionState> GetStateIfExists(std::string name) {
            if (_states.contains(name)) return _states[name];  // TODO use find
            return nullptr;
        }
        std::shared_ptr<InjectionState> FindOrCreateState(const std::string& name) {
            if (_states.contains(name)) return _states[name];  // TODO use find
            auto state    = std::make_shared<InjectionState>(name, _variables);
            _states[name] = state;
            return state;
        }

    public:
        InjectionApp(const std::string& name)
            : _name(name), _variables(std::make_shared<InjectionVariables>()) {}

        const std::string& GetName() const { return _name; }

        InjectionApp& On(
            const std::string& stateName, std::function<void(InjectionBuilder&)> block
        ) {
            Log("[{}] On: {}", _name, stateName);
            auto state   = FindOrCreateState(stateName);
            auto builder = std::make_shared<InjectionBuilder>(_variables);
            builder->SetActionsContainer(state->GetActions());
            block(*builder);
            return *this;
        }
        InjectionApp& OnInstall(std::function<void(InjectionBuilder&)> block) {
            return On("Install", block);
        }
        InjectionApp& OnUninstall(std::function<void(InjectionBuilder&)> block) {
            return On("Uninstall", block);
        }
        void Goto(const std::string& stateName) {
            Log("[{}] Goto: {}", _name, stateName);
            auto state = GetStateIfExists(stateName);
            if (!state) {
                Log("[{}] Goto: {} - State not found", _name, stateName);
                return;
            }
            auto actions = state->GetActions();
            for (auto action : *actions) {
                auto builder                = std::make_shared<InjectionBuilder>(_variables);
                auto actionActionsContainer = action->GetActionContainer();
                if (actionActionsContainer) builder->SetActionsContainer(actionActionsContainer);
                else builder->SetActionsContainer(actions);
                action->Builder = builder;
                action->Perform(_variables);
            }
        }
        InjectionApp& Configure(std::function<void(InjectionBuilder&)> block) {
            Log("[{}] Configure", _name);
            On("Configure", block);
            Goto("Configure");  // <--- Configure() actions are run immediately
            return *this;
        }
        void Install() {
            _isInstalled = true;
            Goto("Install");
        }
        void Uninstall() {
            _isInstalled = false;
            Goto("Uninstall");
        }
        void Toggle() {
            if (_isInstalled) Uninstall();
            else Install();
        }
        bool IsInstalled() const { return _isInstalled; }
    };
}
