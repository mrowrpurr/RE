#pragma once

#include <string_format.h>

#include <string>

#include "Hooks/FunctionTypes.h"
#include "Hooks/Hook.h"
#include "Hooks/Registers.h"
#include "Hooks/Registry.h"

Hooks::Hook& RegisterHook(uint32_t address = 0) {
    auto name = string_format("0x{:x}", address);
    auto hook = Hooks::HookRegistry::GetSingleton().RegisterHook(name);
    if (address != 0) hook->SetAddress(address);
    return *hook;
}

Hooks::Hook& RegisterHook(const std::string& name, uint32_t address = 0) {
    auto hook = Hooks::HookRegistry::GetSingleton().RegisterHook(name);
    if (address != 0) hook->SetAddress(address);
    return *hook;
}

template <uint32_t detourSize>
Hooks::Hook& RegisterHook(const std::string& name, uint32_t address = 0) {
    auto hook = Hooks::HookRegistry::GetSingleton().RegisterHook(name);
    if (address != 0) hook->SetAddress(address);
    hook->SetByteCount(detourSize);
    return *hook;
}

Hooks::Hook& RegisterHook(
    const std::string& name, uint32_t address,
    std::function<void(Hooks::Registers::RegistersReader&)> callable
) {
    return RegisterHook(name, address)
        .CallOriginalBytes()
        .SaveRegisters()
        .Call(callable)
        .RestoreRegisters()
        .JumpBack();
}

template <uint32_t detourSize>
Hooks::Hook& RegisterHook(
    const std::string& name, uint32_t address,
    std::function<void(Hooks::Registers::RegistersReader&)> callable
) {
    return RegisterHook(name, address)
        .SetByteCount(detourSize)
        .CallOriginalBytes()
        .SaveRegisters()
        .Call(callable)
        .RestoreRegisters()
        .JumpBack();
}

template <uint32_t detourSize>
Hooks::Hook& RegisterHook(
    uint32_t address, std::function<void(Hooks::Registers::RegistersReader&)> callable
) {
    return RegisterHook(address)
        .SetByteCount(detourSize)
        .CallOriginalBytes()
        .SaveRegisters()
        .Call(callable)
        .RestoreRegisters()
        .JumpBack();
}

Hooks::Hook& RegisterHook(
    const std::string& name, uint32_t address, Hooks::FunctionTypes::Void functionPtr
) {
    return RegisterHook(name, address)
        .CallOriginalBytes()
        .SaveRegisters()
        .CallFunction(functionPtr)
        .RestoreRegisters()
        .JumpBack();
}

template <uint32_t detourSize>
Hooks::Hook& RegisterHook(
    const std::string& name, uint32_t address, Hooks::FunctionTypes::Void functionPtr
) {
    return RegisterHook(name, address)
        .SetByteCount(detourSize)
        .CallOriginalBytes()
        .SaveRegisters()
        .CallFunction(functionPtr)
        .RestoreRegisters()
        .JumpBack();
}

template <uint32_t detourSize>
Hooks::Hook& RegisterHook(uint32_t address, Hooks::FunctionTypes::Void functionPtr) {
    return RegisterHook(address)
        .SetByteCount(detourSize)
        .CallOriginalBytes()
        .SaveRegisters()
        .CallFunction(functionPtr)
        .RestoreRegisters()
        .JumpBack();
}

Hooks::Hook& RegisterHook(uint32_t address, Hooks::FunctionTypes::Void functionPtr) {
    return RegisterHook(address)
        .CallOriginalBytes()
        .SaveRegisters()
        .CallFunction(functionPtr)
        .RestoreRegisters()
        .JumpBack();
}

// Get all registered hooks
std::unordered_map<std::string, std::shared_ptr<Hooks::Hook>>& GetRegisteredHooks() {
    return Hooks::HookRegistry::GetSingleton().GetHooks();
}
