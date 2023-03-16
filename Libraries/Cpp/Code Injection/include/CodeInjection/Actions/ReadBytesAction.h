#pragma once

#include <Logging.h>
#include <Memory.h>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../InjectionAction.h"

namespace CodeInjection::Actions {

    struct ReadBytesActionParams {
        uintptr_t   address = 0;
        std::string addressVariable;
        std::string outVariable;
        size_t      byteCount;
    };

    class ReadBytesAction : public InjectionAction {
        ReadBytesActionParams _params;

    public:
        ReadBytesAction(ReadBytesActionParams params) : _params(params) {}

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return 0; }

        uintptr_t GetAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.addressVariable.empty()) return vars->Get<uintptr_t>(_params.addressVariable);
            else if (_params.address != 0) return _params.address;
            else if (ActionCurrentAddress != 0) return ActionCurrentAddress;
            else throw std::runtime_error("WriteBytesAction: No address specified");
        }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto address = GetAddress(vars);

            Log("ReadBytesAction: Reading {} bytes from 0x{:X}", _params.byteCount, address);
            auto bytes = Memory::Read(address, _params.byteCount);

            if (_params.outVariable.empty()) throw std::runtime_error("ReadBytesAction: No output variable specified");
            Log("ReadBytesAction: Set output variable {} to {}", _params.outVariable,
                Memory::Bytes{bytes}.ToHexString());
            vars->Set<std::vector<uint8_t>>(_params.outVariable, bytes);
        }
    };
}