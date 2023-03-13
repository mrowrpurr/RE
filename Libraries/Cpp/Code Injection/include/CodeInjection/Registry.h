#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Injection.h"

namespace CodeInjection {
    std::unordered_map<std::string, std::shared_ptr<Injection>> RegisteredInjections;

    void New(const std::string& name) {
        RegisteredInjections[name] = std::make_shared<Injection>(name);
    }

    Injection& GetInjection(const std::string& name) { return *RegisteredInjections[name]; }

    std::vector<std::shared_ptr<Injection>> GetAllInjections() {
        std::vector<std::shared_ptr<Injection>> injections;
        for (auto& injection : RegisteredInjections) injections.push_back(injection.second);
        return injections;
    }

    void InstallAll() {
        for (auto& injection : RegisteredInjections) injection.second->Install();
    }
    void UninstallAll() {
        for (auto& injection : RegisteredInjections) injection.second->Uninstall();
    }
}
