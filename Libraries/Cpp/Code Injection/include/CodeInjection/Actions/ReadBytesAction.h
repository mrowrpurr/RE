#pragma once

#include <cstdint>
#include <string>

#include "../InjectionAction.h"

namespace CodeInjection::Actions {

    struct ReadBytesActionParams {
        uintptr_t   address;
        std::string addressVariable;
        std::string outVariable;
        size_t      byteCount;
    };

    class ReadBytesAction : public InjectionAction {
        ReadBytesActionParams _params;

    public:
        ReadBytesAction(ReadBytesActionParams params) : _params(params) {}

        size_t GetByteCount() const override { return 0; }
        void   Perform(Injection&) override {}
    };
}