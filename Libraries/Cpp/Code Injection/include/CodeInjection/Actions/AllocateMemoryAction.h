#pragma once

#include <Logging.h>

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

        public:
            AllocateMemoryAction(AllocateMemoryActionParams params) : _params(params) {
                _actions = std::make_shared<std::vector<std::shared_ptr<InjectionAction>>>();
            }

            size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return 0; }

            std::shared_ptr<std::vector<std::shared_ptr<InjectionAction>>> GetActionContainer(
            ) override {
                return _actions;
            }

            void Perform(std::shared_ptr<InjectionVariables> vars) override {
                size_t totalRequiredBytes = 0;
                for (auto action : *_actions) totalRequiredBytes += action->GetByteCount(vars);
                Log("Alloc requires {} bytes", totalRequiredBytes);
            }
        };
    }
}
