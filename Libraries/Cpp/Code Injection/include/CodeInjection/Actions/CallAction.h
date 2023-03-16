#pragma once

#include <Memory.h>

#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../InjectionAction.h"

namespace CodeInjection::Actions {

    namespace CallActionController {
        std::atomic<uint32_t>                               _nextCallableId = 0;
        std::unordered_map<uint32_t, std::function<void()>> _callables;

        uint32_t RegisterCallable(std::function<void()> callable) {
            auto callableId        = _nextCallableId++;
            _callables[callableId] = callable;
            return callableId;
        }

        void CallCallable(uint32_t callableId) {
            auto callable = _callables.find(callableId);
            if (callable == _callables.end()) throw std::runtime_error("CallActionController: Callable not found");
            callable->second();
        }
    }

    struct CallActionParams {
        uintptr_t             address;
        std::string           addressVariable;
        std::function<void()> function;  // TODO - support 'Registers'
        bool                  writeProtected = false;
    };

    class CallAction : public InjectionAction {
        CallActionParams _params;
        uint32_t         _callableId;

    public:
        CallAction(CallActionParams params) : _params(params) {
            _callableId = CallActionController::RegisterCallable(_params.function);
        }

        bool IsWriteProtected(std::shared_ptr<InjectionVariables> vars) {
            return _params.writeProtected || CurrentAddressWriteProtected;
        }

        uintptr_t GetAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.addressVariable.empty()) return vars->Get<uintptr_t>(_params.addressVariable);
            else if (_params.address != 0) return _params.address;
            else if (ActionCurrentAddress != 0) return ActionCurrentAddress;
            else throw std::runtime_error("CallAction: No address specified");
        }

        uintptr_t GetAddressToControllerFunction() {
            return reinterpret_cast<uintptr_t>(&CallActionController::CallCallable);
        }

        std::vector<uint8_t> GetBytes(std::shared_ptr<InjectionVariables> vars) {
            auto          address = GetAddress(vars);
            Memory::Bytes bytes;
            bytes.AddByte(0x68);                                                            // 1 byte for the PUSH
            bytes.AddDword(_callableId);                                                    // 4 bytes for the PUSH
            bytes.AddByte(0xE8);                                                            // 1 byte for the CALL
            auto relativeAddress = GetAddressToControllerFunction() - address - 1 - 4 - 5;  // 5 bytes for the CALL
            bytes.AddAddress(relativeAddress);
            bytes.AddBytes({0x83, 0xC4, 0x04});  // ADD ESP, 4 - Clean up the stack
            return bytes.GetBytes();
        }

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return GetBytes(vars).size(); }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto address          = GetAddress(vars);
            auto toAddress        = GetAddressToControllerFunction();
            auto isWriteProtected = IsWriteProtected(vars);
            auto bytes            = GetBytes(vars);

            Log("CallAction: Writing CALL at 0x{:X} to 0x{:x} (Protected: {})", address, toAddress, isWriteProtected);

            if (isWriteProtected) Memory::WriteProtectedBytes(address, bytes);
            else Memory::WriteBytes(address, bytes);
        }
    };
}