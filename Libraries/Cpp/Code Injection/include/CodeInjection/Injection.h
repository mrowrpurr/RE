#pragma once

#include <StatefulApp.h>

#include <string>

namespace CodeInjection {

    class Injection {
        constexpr static const char* VARNAME_ADDRESS = "address";

        std::string      _name;
        StatefulApp::App _app;

    public:
        explicit Injection(const std::string& name) : _name(name) {}

        Injection& SetAddress(uintptr_t address) {
            _app.Set<uintptr_t>(VARNAME_ADDRESS, address);
            return *this;
        }
    };
}
