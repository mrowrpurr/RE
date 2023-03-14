#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "InjectionApp.h"
#include "InjectionBuilder.h"

namespace CodeInjection {
    std::unordered_map<std::string, std::shared_ptr<InjectionApp>> RegisteredInjections;

    InjectionApp& New(const std::string& name) {
        auto injectionApp          = std::make_shared<InjectionApp>(name);
        RegisteredInjections[name] = injectionApp;
        return *injectionApp;
    }

    // Injection& GetInjection(const std::string& name) { return *RegisteredInjections[name]; }

    // std::vector<std::shared_ptr<Injection>> GetAllInjections() {
    //     std::vector<std::shared_ptr<Injection>> injections;
    //     for (auto injection : RegisteredInjections) injections.push_back(injection.second);
    //     return injections;
    // }

    // void InstallAll() {
    //     for (auto injection : RegisteredInjections) injection.second->Install();
    // }
    // void UninstallAll() {
    //     for (auto injection : RegisteredInjections) injection.second->Uninstall();
    // }
}
