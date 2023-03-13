#pragma once

#include <CodeInjection\Actions.h>
#include <CodeInjection\IAction.h>

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace CodeInjection {

    class Injection {
        std::string                           _name;
        std::vector<std::shared_ptr<IAction>> _installActions;
        std::vector<std::shared_ptr<IAction>> _uninstallActions;

    public:
        Injection(std::string name) : _name(name) {}

        Injection& OnInstall(std::function<void(Actions&)> installActions) {
            auto actions = Actions(_installActions);
            installActions(actions);
            return *this;
        }

        Injection& OnUninstall(std::function<void(Actions&)> uninstallActions) {
            auto actions = Actions(_uninstallActions);
            uninstallActions(actions);
            return *this;
        }

        void Install() {
            for (auto& action : _installActions) action->Perform();
        }

        void Uninstall() {
            for (auto& action : _uninstallActions) action->Perform();
        }
    };
}
