#pragma once

#include <StatefulApp/Action.h>

#include <functional>
#include <memory>

namespace CodeInjection {
    class RunFunctionAction : public StatefulApp::Action {
        std::function<void(StatefulApp::Variables&)> _function;

    public:
        RunFunctionAction(std::function<void(StatefulApp::Variables&)> function)
            : _function(function) {}

        RunFunctionAction(std::function<void()> function)
            : _function([function](StatefulApp::Variables&) { function(); }) {}

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            _function(*variables);
        }
    };
}
