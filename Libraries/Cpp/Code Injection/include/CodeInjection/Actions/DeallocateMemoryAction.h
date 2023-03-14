#pragma once

#include <functional>
#include <memory>
#include <string>

#include "../InjectionAction.h"
#include "../InjectionState.h"

namespace CodeInjection {

    class InjectionBuilder;

    namespace Actions {

        struct DeallocateMemoryActionParams {
            std::string addressVariable;
        };

        class DeallocateMemoryAction : public InjectionAction {
            DeallocateMemoryActionParams _params;

        public:
            DeallocateMemoryAction(DeallocateMemoryActionParams params) : _params(params) {}

            size_t GetByteCount() const override { return 0; }

            void Perform(std::shared_ptr<InjectionBuilder> builder) override {}
        };
    }
}
