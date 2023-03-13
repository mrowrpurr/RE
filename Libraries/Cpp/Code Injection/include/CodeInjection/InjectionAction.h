#pragma once

#include <cstdint>

namespace CodeInjection {

    class Injection;

    class InjectionAction {
    public:
        uintptr_t      ActionAddress;
        virtual size_t GetByteCount() const = 0;
        virtual void   Perform(Injection&)  = 0;
    };
}
