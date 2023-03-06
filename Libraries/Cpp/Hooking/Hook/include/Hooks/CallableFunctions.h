#pragma once

#include <atomic>
#include <functional>
#include <unordered_map>

#include "Hooks/Registers.h"

namespace Hooks::CallableFunctions {

    std::atomic<uint32_t> NEXT_FUNCTION_ID = 69;

    std::unordered_map<uint32_t, std::function<void(Registers::RegistersReader&)>> FunctionRegistry;

    uint32_t RegisterFunction(std::function<void(Registers::RegistersReader&)> function) {
        auto functionId              = NEXT_FUNCTION_ID++;
        FunctionRegistry[functionId] = function;
        return functionId;
    }

    void CallHookFunction(uint32_t functionId) {
        auto function = FunctionRegistry[functionId];
        if (function) function(Registers::RegistersReader::GetCurrent());
    }
}