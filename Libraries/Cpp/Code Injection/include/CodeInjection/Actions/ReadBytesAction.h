#pragma once

#include <Memory.h>

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

        void Perform(std::shared_ptr<InjectionBuilder> builder) override {}
        // void Perform(std::shared_ptr<InjectionVariables> vars) override {
        //     auto address = _params.address;
        //     if (!_params.addressVariable.empty())
        //         address = vars->Var<uintptr_t>(_params.addressVariable);
        //     auto bytes = Memory::Read(address, _params.byteCount);
        //     vars->Var<std::vector<uint8_t>>(_params.outVariable, bytes);
        // }
    };
}