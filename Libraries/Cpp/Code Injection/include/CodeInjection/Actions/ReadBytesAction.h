#pragma once

#include <Logging.h>
#include <Memory.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "../InjectionAction.h"

namespace CodeInjection::Actions {

    struct ReadBytesActionParams {
        uintptr_t   address;
        std::string addressVariable;
        std::string outVariable;
        size_t      byteCount;
    };

    class ReadBytesAction : public InjectionAction {
        ReadBytesActionParams _params;

    public:
        ReadBytesAction(ReadBytesActionParams params) : _params(params) {}

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return 0; }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto address = _params.address;
            if (!_params.addressVariable.empty())
                address = vars->Get<uintptr_t>(_params.addressVariable);

            Log("ReadBytesAction: Reading {} bytes from 0x{:X}", _params.byteCount, address);
            auto bytes = Memory::Read(address, _params.byteCount);

            Log("ReadBytesAction: Set output variable {} to {}", _params.outVariable,
                Memory::BytesToString(bytes));
            vars->Set<std::vector<uint8_t>>(_params.outVariable, bytes);
        }
    };
}