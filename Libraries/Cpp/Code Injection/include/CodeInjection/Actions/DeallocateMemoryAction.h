#pragma once

#include <functional>
#include <memory>
#include <string>

#include "../InjectionAction.h"
#include "../InjectionState.h"

namespace CodeInjection {

    namespace Actions {

        struct DeallocateMemoryActionParams {
            std::string addressVariable;
        };

        class DeallocateMemoryAction : public InjectionAction {
            DeallocateMemoryActionParams _params;

        public:
            DeallocateMemoryAction(DeallocateMemoryActionParams params) : _params(params) {}

            size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return 0; }

            void Perform(std::shared_ptr<InjectionVariables> vars) override {}
        };
    }
}
