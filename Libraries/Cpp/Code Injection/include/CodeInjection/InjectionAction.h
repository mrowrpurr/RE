#pragma once

#include <cstdint>
#include <memory>

#include "InjectionVariables.h"

namespace CodeInjection {

    class InjectionAction {
    public:
        uintptr_t      ActionCurrentAddress;
        virtual size_t GetByteCount() const                         = 0;
        virtual void   Perform(std::shared_ptr<InjectionVariables>) = 0;
    };
}
