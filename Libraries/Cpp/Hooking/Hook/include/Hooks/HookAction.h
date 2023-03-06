#pragma once

#include "Hooks/Bytes.h"
#include "Hooks/FunctionTypes.h"

namespace Hooks {

    enum class HookActionType { JMP, CALL, BYTES };

    class HookAction {
        HookActionType      _type;
        Bytes               _bytes;
        FunctionTypes::Void _function;

    public:
        HookAction() = default;
        HookAction(HookActionType type, FunctionTypes::Void function)
            : _type(type), _function(function) {}
        HookAction(HookActionType type, Bytes bytes) : _type(type), _bytes(bytes) {}

        size_t CalculateByteCount() {
            switch (_type) {
                case HookActionType::JMP:
                case HookActionType::CALL:
                    return 5;
                case HookActionType::BYTES:
                    return _bytes.size();
            }
        }
        // GetBytes(ADDRESS)
    };
}
