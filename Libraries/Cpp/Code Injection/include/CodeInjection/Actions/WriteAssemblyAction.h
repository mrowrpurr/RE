#pragma once

#include <Assembly.h>
#include <Memory.h>

#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../InjectionAction.h"

namespace CodeInjection::Actions {

    struct WriteAssemblyActionParams {
        uintptr_t                                  address;
        std::string                                addressVariable;
        std::function<void(Xbyak::CodeGenerator&)> code;
        bool                                       writeProtected = true;
    };

    class WriteAssemblyAction : public InjectionAction {
        WriteAssemblyActionParams _params;
        bool                      _codeGenerated = false;
        std::vector<uint8_t>      _generatedBytes;

    public:
        WriteAssemblyAction(WriteAssemblyActionParams params) : _params(params) {}

        bool IsWriteProtected(std::shared_ptr<InjectionVariables> vars) {
            return _params.writeProtected || CurrentAddressWriteProtected;
        }

        std::vector<uint8_t> GetBytes(std::shared_ptr<InjectionVariables> vars) {
            if (!_codeGenerated) {
                _generatedBytes = Assembly::GetBytes(_params.code);
                _codeGenerated  = true;
            }
            return _generatedBytes;
        }

        uintptr_t GetAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.addressVariable.empty()) return vars->Get<uintptr_t>(_params.addressVariable);
            else if (_params.address != 0) return _params.address;
            else if (ActionCurrentAddress != 0) return ActionCurrentAddress;
            else throw std::runtime_error("WriteAssemblyAction: No address specified");
        }

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return GetBytes(vars).size(); }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto bytes = GetBytes(vars);
            if (bytes.empty()) {
                Log("WriteAssemblyAction: No bytes to write");
                return;
            }

            auto address          = GetAddress(vars);
            auto isWriteProtected = IsWriteProtected(vars);

            Log("WriteAssemblyAction: Writing {} bytes to 0x{:X} (Protected: {})", bytes.size(), address,
                isWriteProtected);

            if (isWriteProtected) Memory::WriteProtectedBytes(address, bytes);
            else Memory::WriteBytes(address, bytes);
        }
    };
}