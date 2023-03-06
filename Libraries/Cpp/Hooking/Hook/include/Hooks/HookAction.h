#pragma once

#include <functional>
#include <optional>

#include "Hooks/Bytes.h"
#include "Hooks/CallableFunctions.h"
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
        uint32_t                                                        _address;
        HookActionType                                                  _type;
        Bytes                                                           _bytes;
        uint32_t                                                        _functionAddress;
        uint32_t                                                        _callableId;
        std::optional<std::function<void(Registers::RegistersReader&)>> _callable;

    public:
        HookAction(HookActionType type) : _type(type) {}
        HookAction(Bytes bytes) : _type(HookActionType::BYTES), _bytes(bytes) {}
        HookAction(std::function<void(Registers::RegistersReader&)> callable)
            : _type(HookActionType::CALL_CALLABLE), _callable(callable) {
            _callableId = CallableFunctions::RegisterFunction(callable);
        }
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
                case HookActionType::JMP_FN:
                case HookActionType::CALL_FN:
                    return 5;
                case HookActionType::BYTES:
                    return _bytes.size();
                case HookActionType::SAVE_REGISTERS:
                case HookActionType::RESTORE_REGISTERS:
                    return 8 * 5;  // 8 registers, 5 bytes each
                case HookActionType::CALL_CALLABLE:
                    return 10;  // PUSH and then CALL
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
                case HookActionType::CALL_CALLABLE:
                    trampoline.WriteProtectedByte(0x68);  // PUSH
                    trampoline.WriteProtectedDword(_callableId);
                    trampoline.WriteProtectedCall(
                        reinterpret_cast<uint32_t>(&CallableFunctions::CallHookFunction)
                    );
                    break;
                default:
                    Log("Unsupported HookActionType: {}", GetTypeName());
            }
        }
    };
}
