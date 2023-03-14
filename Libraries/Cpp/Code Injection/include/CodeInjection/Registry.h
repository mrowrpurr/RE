#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Injection.h"

namespace CodeInjection {
    std::unordered_map<std::string, std::shared_ptr<Injection>> RegisteredInjections;

    Injection& New(const std::string& name) {
        auto injection             = std::make_shared<Injection>(name);
        RegisteredInjections[name] = injection;
        return *injection;
    }

    Injection& GetInjection(const std::string& name) { return *RegisteredInjections[name]; }

    std::vector<std::shared_ptr<Injection>> GetAllInjections() {
        std::vector<std::shared_ptr<Injection>> injections;
        for (auto injection : RegisteredInjections) injections.push_back(injection.second);
        return injections;
    }

    void InstallAll() {
        for (auto injection : RegisteredInjections) injection.second->Install();
    }
    void UninstallAll() {
        for (auto injection : RegisteredInjections) injection.second->Uninstall();
    }
}
