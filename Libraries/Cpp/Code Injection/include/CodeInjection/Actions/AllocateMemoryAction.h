#pragma once

#include <functional>
#include <memory>
#include <string>

#include "../InjectionAction.h"
#include "../InjectionState.h"

namespace CodeInjection {

    class Injection;

    namespace Actions {

        struct AllocateMemoryActionParams {
            std::string                     addressVariable;
            std::function<void(Injection&)> block;
        };

        class AllocateMemoryAction : public InjectionAction {
            AllocateMemoryActionParams _params;

        public:
            AllocateMemoryAction(AllocateMemoryActionParams params) : _params(params) {}

            size_t GetByteCount() const override { return 0; }

            void Perform(std::shared_ptr<InjectionVariables> vars) override {}
        };
    }
}
