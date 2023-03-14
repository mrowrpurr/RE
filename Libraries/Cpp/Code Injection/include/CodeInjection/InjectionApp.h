#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "InjectionBuilder.h"
#include "InjectionState.h"
#include "InjectionVariables.h"

namespace CodeInjection {

    class InjectionApp {
        std::string                                                    _name;
        bool                                                           _isInstalled = false;
        std::shared_ptr<InjectionVariables>                            _variables;
        std::shared_ptr<std::vector<std::shared_ptr<InjectionAction>>> _currentActionsCollection;
        std::shared_ptr<InjectionBuilder>                              _builder;

        std::unordered_map<std::string, std::shared_ptr<InjectionState>> _states;
        std::shared_ptr<InjectionState>                                  _currentState;
        std::shared_ptr<InjectionState>                                  _currentlyConfiguringState;

        std::shared_ptr<InjectionState> GetStateIfExists(std::string name) {
            if (_states.contains(name)) return _states[name];
            return nullptr;
        }
        std::shared_ptr<InjectionState> FindOrCreateState(const std::string& name) {
            if (_states.contains(name)) return _states[name];
            auto state    = std::make_shared<InjectionState>(name, _variables);
            _states[name] = state;
            return state;
        }

    public:
        InjectionApp(const std::string& name) : _name(name) {}

        const std::string& GetName() const { return _name; }

        InjectionApp& On(
            const std::string& stateName, std::function<void(InjectionBuilder&)> block
        ) {
            _currentlyConfiguringState = FindOrCreateState(stateName);
            block(*_builder);
            _currentlyConfiguringState = nullptr;
            return *this;
        }
        InjectionApp& OnInstall(std::function<void(InjectionBuilder&)> block) {
            return On("Install", block);
        }
        InjectionApp& OnUninstall(std::function<void(InjectionBuilder&)> block) {
            return On("Uninstall", block);
        }
        void Goto(const std::string& stateName) {
            auto state = GetStateIfExists(stateName);
            if (state) state->PerformActions();
        }
        InjectionApp& Configure(std::function<void(InjectionBuilder&)> block) {
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
