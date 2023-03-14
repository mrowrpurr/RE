#pragma once

#include <Memory.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "../InjectionAction.h"

namespace CodeInjection::Actions {

    struct WriteBytesActionParams {
        std::string          addressVariable;
        std::vector<uint8_t> bytes;
        std::string          bytesVariable;
    };

    class WriteBytesAction : public InjectionAction {
        WriteBytesActionParams _params;

    public:
        WriteBytesAction(WriteBytesActionParams params) : _params(params) {}

        size_t GetByteCount() const override { return 0; }

        void Perform(std::shared_ptr<InjectionBuilder> builder) override {}
        // void Perform(std::shared_ptr<InjectionVariables> vars) override {
        //     std::vector<uint8_t> bytes;
        //     if (!_params.bytesVariable.empty())
        //         bytes = vars->Var<std::vector<uint8_t>>(_params.bytesVariable);
        //     else
        //         bytes = _params.bytes;
        //     auto address = vars->Var<uintptr_t>(_params.addressVariable);
        //     Memory::WriteProtectedBytes(address, bytes);
        // }
    };
}