#pragma once

namespace CodeInjection {

    class IAction {
    public:
        virtual size_t GetByteCount() const = 0;
        virtual void   Perform()            = 0;
    };
}
