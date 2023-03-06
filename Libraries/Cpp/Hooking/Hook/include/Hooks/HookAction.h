#pragma once

#include <functional>
#include <optional>

#include "Hooks/Bytes.h"
#include "Hooks/FunctionTypes.h"
#include "Hooks/MemoryBytes.h"

namespace Hooks {

    enum class HookActionType {
        BYTES,
        JMP,
        CALL,
        SAVE_REGISTERS,
        RESTORE_REGISTERS,
        CALL_CALLABLE
    };

    namespace HookActionBytes {
        namespace Registers {
            namespace Saving {
                std::vector<uint8_t> SAVE_INSTRUCTION_EAX = {0xA3};
                std::vector<uint8_t> SAVE_INSTRUCTION_EBX = {0x89, 0x1D};
                std::vector<uint8_t> SAVE_INSTRUCTION_ECX = {0x89, 0x0D};
                std::vector<uint8_t> SAVE_INSTRUCTION_EDX = {0x89, 0x15};
                std::vector<uint8_t> SAVE_INSTRUCTION_ESI = {0x89, 0x35};
                std::vector<uint8_t> SAVE_INSTRUCTION_EDI = {0x89, 0x3D};
                std::vector<uint8_t> SAVE_INSTRUCTION_EDP = {0x89, 0x2D};
                std::vector<uint8_t> SAVE_INSTRUCTION_ESP = {0x89, 0x25};
            }
            namespace Restoring {
                std::vector<uint8_t> RESTORE_INSTRUCTION_EAX = {0x8B, 0x05};
                std::vector<uint8_t> RESTORE_INSTRUCTION_EBX = {0x8B, 0x1D};
                std::vector<uint8_t> RESTORE_INSTRUCTION_ECX = {0x8B, 0x0D};
                std::vector<uint8_t> RESTORE_INSTRUCTION_EDX = {0x8B, 0x15};
                std::vector<uint8_t> RESTORE_INSTRUCTION_ESI = {0x8B, 0x35};
                std::vector<uint8_t> RESTORE_INSTRUCTION_EDI = {0x8B, 0x3D};
                std::vector<uint8_t> RESTORE_INSTRUCTION_EDP = {0x8B, 0x2D};
                std::vector<uint8_t> RESTORE_INSTRUCTION_ESP = {0x8B, 0x25};
            }
        }
    }

    // Represents an action which can be taken when a hook is run.
    // So that common actions are easier to setup (although *all* could be done with BYTES)
    class HookAction {
        uint32_t                             _address;
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

        HookActionType GetType() const { return _type; }
        std::string    GetTypeName() const {
            switch (_type) {
                case HookActionType::JMP:
                    return "JMP";
                case HookActionType::CALL:
                    return "CALL";
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
                    trampoline.WriteProtectedJmp((uint32_t)((BYTE*)_function));
                    break;
                case HookActionType::CALL:
                    trampoline.WriteProtectedCall((uint32_t)((BYTE*)_function));
                    break;
                case HookActionType::BYTES:
                    trampoline.WriteProtectedBytes(_bytes);
                    break;
                default:
                    Log("Unsupported HookActionType: {}", GetTypeName());
            }
            // case HookActionType::JMP:
            //     bytes.WriteJmp(_function);
            //     break;
            // case HookActionType::CALL:
            //     bytes.WriteCall(_function);
            //     break;
            // case HookActionType::SAVE_REGISTERS:
            //     bytes.Write(HookActionBytes::Registers::Saving::SAVE_INSTRUCTION_EAX);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Saving::SAVE_INSTRUCTION_EBX);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Saving::SAVE_INSTRUCTION_ECX);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Saving::SAVE_INSTRUCTION_EDX);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Saving::SAVE_INSTRUCTION_ESI);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Saving::SAVE_INSTRUCTION_EDI);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Saving::SAVE_INSTRUCTION_EDP);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Saving::SAVE_INSTRUCTION_ESP);
            //     bytes.Write(0x00);
            //     break;
            // case HookActionType::RESTORE_REGISTERS:
            //     bytes.Write(HookActionBytes::Registers::Restoring::RESTORE_INSTRUCTION_EAX);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Restoring::RESTORE_INSTRUCTION_EBX);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Restoring::RESTORE_INSTRUCTION_ECX);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Restoring::RESTORE_INSTRUCTION_EDX);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Restoring::RESTORE_INSTRUCTION_ESI);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Restoring::RESTORE_INSTRUCTION_EDI);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Restoring::RESTORE_INSTRUCTION_EDP);
            //     bytes.Write(0x00);
            //     bytes.Write(HookActionBytes::Registers::Restoring::RESTORE_INSTRUCTION_ESP);
            //     bytes.Write(0x00);
            //     break;
            // case HookActionType::CALL_CALLABLE:
            //     bytes.WriteCall(_callable.value());
            //     break;
            // }
        }
    };
}

// if (_trampoline_writeOriginalBytesAtStart)

// for (auto functionPtrToJmpTo : _functionPtrsCalculateToJmpTo)

// if (_trampoline_jumpBackToOriginalAddressAtEnd)
//     _trampoline.WriteProtectedJmp(GetJumpBackAddress());