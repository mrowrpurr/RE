#pragma once

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

            std::shared_ptr<std::vector<std::shared_ptr<InjectionAction>>> GetActions() const {
                return _actions;
            }

            size_t GetByteCount() const override { return 0; }

            void Perform(std::shared_ptr<InjectionBuilder> builder) override {}
        };
    }
}
