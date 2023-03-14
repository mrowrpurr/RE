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
        std::string _name;
        bool        _isInstalled = false;
        //     false; std::shared_ptr<InjectionVariables>                              _variables;
        //     std::unordered_map<std::string, std::shared_ptr<InjectionState>> _states;
        //     std::shared_ptr<InjectionState>                                  _currentState;
        //     std::shared_ptr<InjectionState> _currentlyConfiguringState;

        //     std::shared_ptr<InjectionState> GetStateIfExists(std::string name) {
        //         if (_states.contains(name)) return _states[name];
        //         return nullptr;
        //     }
        //     std::shared_ptr<InjectionState> FindOrCreateState(const std::string& name) {
        //         if (_states.contains(name)) return _states[name];
        //         auto state    = std::make_shared<InjectionState>(name, _variables);
        //         _states[name] = state;
        //         return state;
        //     }

    public:
        InjectionApp(const std::string& name) : _name(name) {}

        const std::string& GetName() const { return _name; }

        bool IsInstalled() const { return _isInstalled; }
        void Install() {}
        void Uninstall() {}
        void Toggle() {
            if (_isInstalled) Uninstall();
            else Install();
        }
    };
}
