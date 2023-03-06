#pragma once

#include <functional>
#include <optional>

#include "Hooks/Bytes.h"
#include "Hooks/FunctionTypes.h"

namespace Hooks {

    enum class HookActionType {
        BYTES,
        JMP,
        CALL,
        SAVE_REGISTERS,
        RESTORE_REGISTERS,
        CALL_CALLABLE
    };

    // Represents an action which can be taken when a hook is run.
    // So that common actions are easier to setup (although *all* could be done with BYTES)
    class HookAction {
        HookActionType                       _type;
        Bytes                                _bytes;
        FunctionTypes::Void                  _function;
        std::optional<std::function<void()>> _callable;

    public:
        HookAction(HookActionType type) : _type(type) {}
        HookAction(Bytes bytes) : _type(HookActionType::BYTES), _bytes(bytes) {}
        HookAction(std::function<void()> callable)
            : _type(HookActionType::CALL_CALLABLE), _callable(callable) {}
        HookAction(HookActionType type, FunctionTypes::Void function)
            : _type(type), _function(function) {}

        size_t CalculateByteCount() {
            switch (_type) {
                case HookActionType::JMP:
                case HookActionType::CALL:
                    return 5;
                case HookActionType::BYTES:
                    return _bytes.size();
                default:
                    return 0;
            }
        }

        // GetBytes(ADDRESS)
    };
}
