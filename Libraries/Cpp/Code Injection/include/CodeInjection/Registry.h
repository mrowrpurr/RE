#pragma once

#include <CodeInjection\Injection.h>

#include <memory>
#include <string>
#include <unordered_map>

namespace CodeInjection {
    std::unordered_map<std::string, std::shared_ptr<Injection>> RegisteredInjections;

    void New(std::string name) { RegisteredInjections[name] = std::make_shared<Injection>(name); }

    Injection& Get(std::string name) { return *RegisteredInjections[name]; }

    std::vector<std::shared_ptr<Injection>> GetAll() {
        std::vector<std::shared_ptr<Injection>> injections;
        for (auto& injection : RegisteredInjections) injections.push_back(injection.second);
        return injections;
    }

    void Install(std::string name) { RegisteredInjections[name]->Install(); }

    void Uninstall(std::string name) { RegisteredInjections[name]->Uninstall(); }

    void InstallAll() {
        for (auto& injection : RegisteredInjections) injection.second->Install();
    }

    void UninstallAll() {
        for (auto& injection : RegisteredInjections) injection.second->Uninstall();
    }
}
