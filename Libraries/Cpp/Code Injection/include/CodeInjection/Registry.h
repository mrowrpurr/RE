#pragma once

#include <Logging.h>

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "InjectionApp.h"
#include "Registers.h"

namespace CodeInjection {
    std::unordered_map<std::string, std::shared_ptr<InjectionApp>> RegisteredInjections;

    InjectionApp& New(const std::string& name) {
        auto injectionApp          = std::make_shared<InjectionApp>(name);
        RegisteredInjections[name] = injectionApp;
        Log("[{}] Register", name);
        return *injectionApp;
    }

    InjectionApp& InjectFunction(
        const std::string& name, uintptr_t address, std::function<void(Registers::RegistersReader&)> code,
        size_t detourSize = 5
    ) {
        auto injectionApp          = std::make_shared<InjectionApp>(name);
        RegisteredInjections[name] = injectionApp;
        Log("[{}] Register Injected Function", name);

        injectionApp
            ->Configure([address, detourSize](Injection& _) {
                _.Var<uintptr_t>("Detour", address);
                _.Var<size_t>("DetourSize", detourSize);
                _.Var<uintptr_t>("JumpBack", _.Var<uintptr_t>("Detour") + _.Var<size_t>("DetourSize"));
                _.Var<uintptr_t>("Trampoline", 0);
                _.Var<uintptr_t>("DetourNopAddress", _.Var<uintptr_t>("Detour") + 5);
                _.ReadBytes("Detour", "OriginalBytes", _.Var<size_t>("DetourSize"));
            })
            .OnInstall([code](Injection& _) {
                _.AllocateMemory("Trampoline", [code](Injection& trampoline) {
                    trampoline.SaveGeneralPurposeRegisters();
                    trampoline.Call(code);
                    trampoline.RestoreGeneralPurposeRegisters();
                    trampoline.WriteBytes("OriginalBytes");
                    trampoline.WriteJmp("JumpBack");
                });
                _.WriteJmp("Detour", "Trampoline");
                if (_.Var<size_t>("DetourSize") > 5) _.WriteNop("DetourNopAddress", _.Var<size_t>("DetourSize") - 5);
            })
            .OnUninstall([](Injection& _) {
                _.WriteBytes("Detour", "OriginalBytes");
                _.DeallocateMemory("Trampoline");
            });

        return *injectionApp;
    }

    template <size_t N>
    InjectionApp& InjectFunction(
        const std::string& name, uintptr_t address, std::function<void(Registers::RegistersReader&)> code
    ) {
        return InjectFunction(name, address, code, N);
    }

    void UninstallAll() {
        for (auto& [name, injectionApp] : RegisteredInjections) injectionApp->Uninstall();
    }
}
