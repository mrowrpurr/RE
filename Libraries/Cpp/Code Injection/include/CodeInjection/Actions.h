#pragma once

#include <CodeInjection\IAction.h>

#include <vector>

namespace CodeInjection {

    class Actions {
        std::vector<std::shared_ptr<IAction>>& _actions;

    public:
        Actions(std::vector<std::shared_ptr<IAction>>& actions) : _actions(actions) {}

        template <typename T, typename... Args>
        Actions& AddAction(Args&&... args) {
            _actions.push_back(std::make_shared<T>(std::forward<Args>(args)...));
            return *this;
        }
    };
}
