#pragma once

#include <CodeInjecting/CodeInjectionAction.h>

namespace CodeInjecting::Actions {
    class DeallocateMemory : public CodeInjectionAction {
    public:
        void Perform() override {}
    };
}
