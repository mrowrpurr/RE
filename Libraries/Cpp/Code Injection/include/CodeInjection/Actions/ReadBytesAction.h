#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

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

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            vars->Var<std::vector<uint8_t>>(_params.outVariable, {0x69, 0x42, 0x69, 0x42});
        }
    };
}