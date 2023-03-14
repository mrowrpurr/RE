#pragma once

#include <cstdint>
#include <memory>

#include "InjectionVariables.h"

namespace CodeInjection {

    class InjectionBuilder;

    class InjectionAction {
    public:
        uintptr_t    ActionCurrentAddress;
        virtual bool HasChildActions() const { return false; }
        std::shared_ptr<std::vector<std::shared_ptr<InjectionAction>>> GetChildActions() const {
            return nullptr;
        }
        virtual size_t GetByteCount() const                       = 0;
        virtual void   Perform(std::shared_ptr<InjectionBuilder>) = 0;
    };
}
