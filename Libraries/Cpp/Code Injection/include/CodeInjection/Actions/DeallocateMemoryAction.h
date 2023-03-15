#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include "../InjectionAction.h"
#include "../InjectionState.h"

namespace CodeInjection {

    namespace Actions {

        struct DeallocateMemoryActionParams {
            uintptr_t   address;
            std::string addressVariable;
        };

        class DeallocateMemoryAction : public InjectionAction {
            DeallocateMemoryActionParams _params;

        public:
            uintptr_t GetAddress(std::shared_ptr<InjectionVariables> vars) {
                if (!_params.addressVariable.empty())
                    return vars->Get<uintptr_t>(_params.addressVariable);
                else if (_params.address != 0) return _params.address;
                else if (ActionCurrentAddress != 0) return ActionCurrentAddress;
                else throw std::runtime_error("DeallocateMemoryAction: No address specified");
            }

            DeallocateMemoryAction(DeallocateMemoryActionParams params) : _params(params) {}

            size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return 0; }

            void Perform(std::shared_ptr<InjectionVariables> vars) override {
                auto address = GetAddress(vars);
                if (address == 0) {
                    Log("DeallocateMemoryAction: Address is 0, not deallocating");
                    return;
                }
                Log("DeallocateMemoryAction: Deallocating memory at 0x{:X}", address);
                Memory::Free(address);
            }
        };
    }
}
