#pragma once

#include <Memory.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "../InjectionAction.h"

namespace CodeInjection::Actions {

    struct WriteBytesActionParams {
        std::string          addressVariable;
        std::vector<uint8_t> bytes;
        std::string          bytesVariable;
        bool                 writeProtected = true;
    };

    class WriteBytesAction : public InjectionAction {
        WriteBytesActionParams _params;

    public:
        WriteBytesAction(WriteBytesActionParams params) : _params(params) {}

        std::vector<uint8_t> GetBytes(std::shared_ptr<InjectionVariables> vars) {
            std::vector<uint8_t> bytes;
            if (!_params.bytesVariable.empty())
                bytes = vars->Get<std::vector<uint8_t>>(_params.bytesVariable);
            else bytes = _params.bytes;
            return bytes;
        }

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override {
            // return GetBytes(nullptr).size();
            return 0;
        }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto bytes   = GetBytes(vars);
            auto address = vars->Get<uintptr_t>(_params.addressVariable);

            Log("WriteBytesAction: Writing {} bytes to 0x{:X}: {} (Protected: {})", bytes.size(),
                address, Memory::BytesToString(bytes), _params.writeProtected);

            if (_params.writeProtected) Memory::WriteProtectedBytes(address, bytes);
            else Memory::WriteBytes(address, bytes);
        }
    };
}