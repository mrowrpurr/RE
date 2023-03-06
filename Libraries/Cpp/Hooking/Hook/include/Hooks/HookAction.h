#pragma once

#include <functional>
#include <optional>

#include "Hooks/Bytes.h"
#include "Hooks/MemoryBytes.h"
#include "Hooks/Registers.h"

namespace Hooks {

    enum class HookActionType {
        BYTES,
        JMP,
        CALL,
        JMP_FN,
        CALL_FN,
        SAVE_REGISTERS,
        RESTORE_REGISTERS,
        CALL_CALLABLE
    };

    // Represents an action which can be taken when a hook is run.
    // So that common actions are easier to setup (although *all* could be done with BYTES)
    class HookAction {
        uint32_t                             _address;
        HookActionType                       _type;
        Bytes                                _bytes;
        uint32_t                             _functionAddress;
        std::optional<std::function<void()>> _callable;

    public:
        HookAction(HookActionType type) : _type(type) {}
        HookAction(Bytes bytes) : _type(HookActionType::BYTES), _bytes(bytes) {}
        HookAction(std::function<void()> callable)
            : _type(HookActionType::CALL_CALLABLE), _callable(callable) {}
        HookAction(HookActionType type, uint32_t address) : _type(type) {
            if (type == HookActionType::JMP_FN || type == HookActionType::CALL_FN)
                _functionAddress = address;
            else
                _address = address;
        }

        HookActionType GetType() const { return _type; }
        std::string    GetTypeName() const {
            switch (_type) {
                case HookActionType::JMP:
                    return "JMP";
                case HookActionType::CALL:
                    return "CALL";
                case HookActionType::JMP_FN:
                    return "JMP_FN";
                case HookActionType::CALL_FN:
                    return "CALL_FN";
                case HookActionType::BYTES:
                    return "BYTES";
                case HookActionType::SAVE_REGISTERS:
                    return "SAVE_REGISTERS";
                case HookActionType::RESTORE_REGISTERS:
                    return "RESTORE_REGISTERS";
                case HookActionType::CALL_CALLABLE:
                    return "CALL_CALLABLE";
                default:
                    return "UNKNOWN";
            }
        }

        size_t CalculateByteCount() {
            switch (_type) {
                case HookActionType::JMP:
                case HookActionType::CALL:
                    return 5;
                case HookActionType::BYTES:
                    return _bytes.size();
                case HookActionType::SAVE_REGISTERS:
                case HookActionType::RESTORE_REGISTERS:
                    return 8 * 5;
                default:
                    return 0;
            }
        }

        void Write(MemoryBytes& trampoline) {
            switch (_type) {
                case HookActionType::JMP:
                    trampoline.WriteProtectedJmp(_address);
                    break;
                case HookActionType::CALL:
                    trampoline.WriteProtectedCall(_address);
                    break;
                case HookActionType::JMP_FN:
                    trampoline.WriteProtectedJmp(_functionAddress);
                    break;
                case HookActionType::CALL_FN:
                    trampoline.WriteProtectedCall(_functionAddress);
                    break;
                case HookActionType::BYTES:
                    trampoline.WriteProtectedBytes(_bytes);
                    break;
                case HookActionType::SAVE_REGISTERS:
                    Registers::Instructions::WriteSaveBytes(trampoline);
                    break;
                case HookActionType::RESTORE_REGISTERS:
                    Registers::Instructions::WriteRestoreBytes(trampoline);
                    break;
                default:
                    Log("Unsupported HookActionType: {}", GetTypeName());
            }
            // case HookActionType::CALL_CALLABLE:
            //     bytes.WriteCall(_callable.value());
            //     break;
            // }
        }
    };
}
