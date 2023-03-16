#pragma once

#include <Memory.h>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../InjectionAction.h"

namespace CodeInjection::Actions {

    struct WriteNopActionParams {
        uintptr_t   address = 0;
        std::string addressVariable;
        size_t      count;
        bool        writeProtected = true;
    };

    class WriteNopAction : public InjectionAction {
        WriteNopActionParams _params;

    public:
        WriteNopAction(WriteNopActionParams params) : _params(params) {}

        bool IsWriteProtected(std::shared_ptr<InjectionVariables> vars) {
            return _params.writeProtected || CurrentAddressWriteProtected;
        }

        uintptr_t GetAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.addressVariable.empty()) return vars->Get<uintptr_t>(_params.addressVariable);
            else if (_params.address != 0) return _params.address;
            else if (ActionCurrentAddress != 0) return ActionCurrentAddress;
            else throw std::runtime_error("WriteNopAction: No address specified");
        }

        std::vector<uint8_t> GetBytes(std::shared_ptr<InjectionVariables> vars) {
            std::vector<uint8_t> bytes;
            for (size_t i = 0; i < _params.count; i++) bytes.push_back(0x90);  // NOP
            return bytes;
        }

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return GetBytes(vars).size(); }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto address          = GetAddress(vars);
            auto bytes            = GetBytes(vars);
            auto isWriteProtected = IsWriteProtected(vars);

            Log("WriteNopAction: Writing {} NOP bytes to 0x{:x} (Protected: {})", bytes.size(), address,
                isWriteProtected);

            if (isWriteProtected) Memory::WriteProtected(address, bytes);
            else Memory::Write(address, bytes);
        }
    };
}