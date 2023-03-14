#pragma once

#include <Logging.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "InjectionApp.h"

namespace CodeInjection {
    std::unordered_map<std::string, std::shared_ptr<InjectionApp>> RegisteredInjections;

    InjectionApp& New(const std::string& name) {
        auto injectionApp          = std::make_shared<InjectionApp>(name);
        RegisteredInjections[name] = injectionApp;
        Log("[{}] Register", name);
        return *injectionApp;
    }
}
