#pragma once

#include <Memory.h>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../InjectionAction.h"

namespace CodeInjection::Actions {

    struct WriteBytesActionParams {
        uintptr_t            address;
        std::string          addressVariable;
        std::vector<uint8_t> bytes;
        std::string          bytesVariable;
        bool                 writeProtected = true;
    };

    class WriteBytesAction : public InjectionAction {
        WriteBytesActionParams _params;

    public:
        WriteBytesAction(WriteBytesActionParams params) : _params(params) {}

        bool IsWriteProtected(std::shared_ptr<InjectionVariables> vars) {
            return _params.writeProtected || CurrentAddressWriteProtected;
        }

        std::vector<uint8_t> GetBytes(std::shared_ptr<InjectionVariables> vars) {
            std::vector<uint8_t> bytes;
            if (!_params.bytesVariable.empty())
                bytes = vars->Get<std::vector<uint8_t>>(_params.bytesVariable);
            else bytes = _params.bytes;
            return bytes;
        }

        uintptr_t GetAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.addressVariable.empty())
                return vars->Get<uintptr_t>(_params.addressVariable);
            else if (_params.address != 0) return _params.address;
            else if (ActionCurrentAddress != 0) return ActionCurrentAddress;
            else throw std::runtime_error("WriteBytesAction: No address specified");
        }

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override {
            return GetBytes(vars).size();
        }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto bytes = GetBytes(vars);
            if (bytes.empty()) {
                Log("WriteBytesAction: No bytes to write");
                return;
            }

            auto address          = GetAddress(vars);
            auto isWriteProtected = IsWriteProtected(vars);

            Log("WriteBytesAction: Writing {} bytes to 0x{:X}: {} (Protected: {})", bytes.size(),
                address, Memory::BytesToString(bytes), isWriteProtected);

            if (isWriteProtected) Memory::WriteProtectedBytes(address, bytes);
            else Memory::WriteBytes(address, bytes);
        }
    };
}