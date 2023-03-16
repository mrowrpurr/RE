#pragma once

#include <Memory.h>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../InjectionAction.h"

namespace CodeInjection::Actions {

    struct WriteCallActionParams {
        uintptr_t   fromAddress;
        std::string fromAddressVariable;
        uintptr_t   toAddress;
        std::string toAddressVariable;
        bool        writeProtected = true;
    };

    class WriteCallAction : public InjectionAction {
        WriteCallActionParams _params;

    public:
        WriteCallAction(WriteCallActionParams params) : _params(params) {}

        bool IsWriteProtected(std::shared_ptr<InjectionVariables> vars) {
            return _params.writeProtected || CurrentAddressWriteProtected;
        }

        uintptr_t GetToAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.toAddressVariable.empty()) return vars->Get<uintptr_t>(_params.toAddressVariable);
            else if (_params.toAddress != 0) return _params.toAddress;
            else throw std::runtime_error("WriteCallAction: No address specified");
        }

        uintptr_t GetFromAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.fromAddressVariable.empty()) return vars->Get<uintptr_t>(_params.fromAddressVariable);
            else if (_params.fromAddress != 0) return _params.fromAddress;
            else if (ActionCurrentAddress != 0) return ActionCurrentAddress;
            else throw std::runtime_error("WriteCallAction: No address specified");
        }

        std::vector<uint8_t> GetBytes(std::shared_ptr<InjectionVariables> vars) {
            auto          toAddress   = GetToAddress(vars);
            auto          fromAddress = GetFromAddress(vars);
            Memory::Bytes bytes;
            bytes.AddByte(0xE8);                                 // CALL
            auto relativeAddress = toAddress - fromAddress - 5;  // 5 bytes for the CALL
            bytes.AddAddress(relativeAddress);
            return bytes.GetBytes();
        }

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return GetBytes(vars).size(); }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto fromAddress      = GetFromAddress(vars);
            auto toAddress        = GetToAddress(vars);
            auto isWriteProtected = IsWriteProtected(vars);
            auto bytes            = GetBytes(vars);

            Log("WriteCallAction: Writing CALL at 0x{:X} to 0x{:x} (Protected: {})", fromAddress, toAddress,
                isWriteProtected);

            if (isWriteProtected) Memory::WriteProtected(fromAddress, bytes);
            else Memory::Write(fromAddress, bytes);
        }
    };
}