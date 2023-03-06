#pragma once

#include <string>

#include "Hooks/Hook.h"
#include "Hooks/Registry.h"

// Register a hook with the given name
Hooks::Hook& RegisterHook(const std::string& name) {
    return *Hooks::HookRegistry::GetSingleton().RegisterHook(name);
}

// Get all registered hooks
std::unordered_map<std::string, std::shared_ptr<Hooks::Hook>>& GetRegisteredHooks() {
    return Hooks::HookRegistry::GetSingleton().GetHooks();
}
