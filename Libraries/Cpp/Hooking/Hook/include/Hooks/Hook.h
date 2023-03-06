#pragma once

#include <functional>
#include <optional>
#include <string>

namespace Hooks {

    // Represents a hook to a specific address implemented via a JMP
    class Hook {
        std::string                          _name;
        bool                                 _installed = false;
        std::optional<std::function<void()>> _installFunction;
        std::optional<std::function<void()>> _uninstallFunction;

    public:
        const std::string& GetName() const { return _name; }
        Hook&              SetName(const std::string& name) {
            _name = name;
            return *this;
        }

        bool IsInstalled() const { return _installed; }

        // Set the function to be called when the hook is installed
        Hook& SetInstallFunction(const std::function<void()>& installFunction) {
            _installFunction = installFunction;
            return *this;
        }

        // Set the function to be called when the hook is uninstalled
        Hook& SetUninstallFunction(const std::function<void()>& uninstallFunction) {
            _uninstallFunction = uninstallFunction;
            return *this;
        }

        void Install() {
            if (_installFunction.has_value()) _installFunction.value()();
            // Else ...
        }

        void Uninstall() {
            if (_uninstallFunction.has_value()) _uninstallFunction.value()();
            // Else ...
        }

        bool Toggle() {
            if (_installed)
                Uninstall();
            else
                Install();
            _installed = !_installed;
            return _installed;
        }
    };
}
