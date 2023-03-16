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

    struct FindBytesActionParams {
        std::string          module;
        std::string          moduleVariable;
        std::string          bytesString;
        std::string          bytesStringVariable;
        std::vector<uint8_t> bytes;
        std::string          bytesVariable;
        std::string          mask;
        std::string          maskVariable;
        uintptr_t            startOffset = 0;
        std::string          startOffsetVariable;
        std::string          outVariable;
    };

    class FindBytesAction : public InjectionAction {
        FindBytesActionParams _params;

    public:
        FindBytesAction(FindBytesActionParams params) : _params(params) {}

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return 0; }

        std::string GetModuleName(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.moduleVariable.empty()) return vars->Get<std::string>(_params.moduleVariable);
            return _params.module;
        }

        std::vector<uint8_t> GetBytes(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.bytesVariable.empty()) return vars->Get<std::vector<uint8_t>>(_params.bytesVariable);
            return _params.bytes;
        }

        std::string GetBytesString(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.bytesStringVariable.empty()) return vars->Get<std::string>(_params.bytesStringVariable);
            return _params.bytesString;
        }

        std::string GetMask(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.maskVariable.empty()) return vars->Get<std::string>(_params.maskVariable);
            else if (!_params.mask.empty()) return _params.mask;
            else return {};
        }

        uintptr_t GetStartOffset(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.startOffsetVariable.empty()) return vars->Get<uintptr_t>(_params.startOffsetVariable);
            return _params.startOffset;
        }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto moduleName  = GetModuleName(vars);
            auto bytesVector = GetBytes(vars);
            auto bytesString = GetBytesString(vars);
            auto mask        = GetMask(vars);
            auto startOffset = GetStartOffset(vars);

            Memory::Bytes bytes;
            if (bytesVector.empty())
                if (bytesString.empty()) throw std::runtime_error("FindBytesAction: No bytes or bytesString provided");
                else bytes = Memory::Bytes::FromString(bytesString);
            else bytes = bytesVector;

            // Remove me
            Log("!!! Bytes: {}", bytes.ToHexString());

            Log("FindBytesAction: Searching for {} (mask: '{}') in module {}", bytes.ToHexString(), mask, moduleName);
            auto address = Memory::Find(moduleName, bytes, mask, startOffset);
            if (address == 0) {
                Log("FindBytesAction: Failed to find bytes in module {}", moduleName);
                vars->Set<uintptr_t>(_params.outVariable, 0);
            } else {
                Log("FindBytesAction: Found bytes in module {} at address {:x}", moduleName, address);
                vars->Set<uintptr_t>(_params.outVariable, address);
            }
        }
    };
}