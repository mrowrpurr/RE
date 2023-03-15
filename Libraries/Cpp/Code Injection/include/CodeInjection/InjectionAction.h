#pragma once

#include <cstdint>
#include <memory>

#include "InjectionVariables.h"

namespace CodeInjection {

    class InjectionBuilder;

    class InjectionAction {
    public:
        uintptr_t                         ActionCurrentAddress;
        bool                              CurrentAddressWriteProtected = false;
        std::shared_ptr<InjectionBuilder> Builder;

        virtual size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) = 0;
        virtual std::shared_ptr<std::vector<std::shared_ptr<InjectionAction>>> GetActionContainer(
        ) {
            return nullptr;
        }
        virtual void Perform(std::shared_ptr<InjectionVariables>) = 0;
    };
}
