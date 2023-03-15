#pragma once

#include <Logging.h>
#include <Memory.h>

#include <functional>
#include <memory>
#include <string>

#include "../InjectionAction.h"
#include "../InjectionState.h"

namespace CodeInjection {

    class InjectionBuilder;

    namespace Actions {

        struct AllocateMemoryActionParams {
            std::string                            addressVariable;
            std::function<void(InjectionBuilder&)> code;
        };

        class AllocateMemoryAction : public InjectionAction {
            AllocateMemoryActionParams                                     _params;
            std::shared_ptr<std::vector<std::shared_ptr<InjectionAction>>> _actions;
            bool                                                           _hasBeenRun = false;
            size_t                                                         _totalRequiredBytes = 0;

        public:
            AllocateMemoryAction(AllocateMemoryActionParams params) : _params(params) {
                _actions = std::make_shared<std::vector<std::shared_ptr<InjectionAction>>>();
            }

            void RunBlockToPopulateActions(
                std::function<void(InjectionBuilder&)> block,
                std::shared_ptr<InjectionVariables>    vars
            ) {
                if (_hasBeenRun) return;
                else _hasBeenRun = true;
                _params.code(*Builder);
                for (auto action : *_actions) _totalRequiredBytes += action->GetByteCount(vars);
            }

            size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override {
                return _totalRequiredBytes;
            }

            std::shared_ptr<std::vector<std::shared_ptr<InjectionAction>>> GetActionContainer(
            ) override {
                return _actions;
            }

            void Perform(std::shared_ptr<InjectionVariables> vars) override {
                RunBlockToPopulateActions(_params.code, vars);
                Log("Alloc requires {} bytes", _totalRequiredBytes);

                auto address = Memory::Allocate(_totalRequiredBytes);
                Log("Allocated memory at address 0x{:X}", address);

                vars->Set<uintptr_t>(_params.addressVariable, address);

                size_t offset = 0;
                for (auto action : *_actions) {
                    action->ActionCurrentAddress         = address + offset;
                    action->CurrentAddressWriteProtected = false;
                    action->Perform(vars);
                    offset += action->GetByteCount(vars);
                }
            }
        };
    }
}
