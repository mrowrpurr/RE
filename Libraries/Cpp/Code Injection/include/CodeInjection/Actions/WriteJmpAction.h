#pragma once

#include <Memory.h>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../InjectionAction.h"

namespace CodeInjection::Actions {

    struct WriteJmpActionParams {
        uintptr_t   address;
        std::string addressVariable;
        uintptr_t   fromAddress;
        std::string fromAddressVariable;
        uintptr_t   toAddress;
        std::string toAddressVariable;
        bool        writeProtected = true;
    };

    class WriteJmpAction : public InjectionAction {
        WriteJmpActionParams _params;

    public:
        WriteJmpAction(WriteJmpActionParams params) : _params(params) {}

        bool IsWriteProtected(std::shared_ptr<InjectionVariables> vars) {
            return _params.writeProtected || CurrentAddressWriteProtected;
        }

        uintptr_t GetAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.addressVariable.empty()) return vars->Get<uintptr_t>(_params.addressVariable);
            else if (_params.address != 0) return _params.address;
            else if (ActionCurrentAddress != 0) return ActionCurrentAddress;
            else throw std::runtime_error("WriteJmpAction: No address specified");
        }

        uintptr_t GetToAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.toAddressVariable.empty()) return vars->Get<uintptr_t>(_params.toAddressVariable);
            else if (_params.toAddress != 0) return _params.toAddress;
            else throw std::runtime_error("WriteJmpAction: No address specified");
        }

        uintptr_t GetFromAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.fromAddressVariable.empty()) return vars->Get<uintptr_t>(_params.fromAddressVariable);
            else if (_params.fromAddress != 0) return _params.fromAddress;
            else if (!_params.addressVariable.empty()) return vars->Get<uintptr_t>(_params.addressVariable);
            else if (_params.address != 0) return _params.address;
            else if (ActionCurrentAddress != 0) return ActionCurrentAddress;
            else throw std::runtime_error("WriteJmpAction: No address specified");
        }

        std::vector<uint8_t> GetBytes(std::shared_ptr<InjectionVariables> vars) {
            auto          toAddress   = GetToAddress(vars);
            auto          fromAddress = GetFromAddress(vars);
            Memory::Bytes bytes;
            bytes.AddByte(0xE9);                                 // JMP
            auto relativeAddress = toAddress - fromAddress - 5;  // 5 bytes for the JMP
            bytes.AddAddress(relativeAddress);
            return bytes.GetBytes();
        }

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return GetBytes(vars).size(); }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto address          = GetAddress(vars);
            auto toAddress        = GetToAddress(vars);
            auto fromAddress      = GetFromAddress(vars);
            auto isWriteProtected = IsWriteProtected(vars);
            auto bytes            = GetBytes(vars);

            Log("WriteJmpAction: Writing JMP at 0x{:X} to 0x{:X} from 0x{:X} (Protected: {})", address, toAddress,
                fromAddress, isWriteProtected);

            if (isWriteProtected) Memory::WriteProtectedBytes(address, bytes);
            else Memory::WriteBytes(address, bytes);
        }
    };
}