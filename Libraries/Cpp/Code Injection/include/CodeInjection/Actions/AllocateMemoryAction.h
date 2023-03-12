#pragma once

#include <Memory.h>
#include <StatefulApp.h>

#include "CodeInjection/Actions/AllocatedMemoryActionBuilder.h"
#include "CodeInjection/Actions/ByteWriterActionGroup.h"

namespace CodeInjection {
    class AllocateMemoryAction : public ByteWriterActionGroup {
        std::string _addressVariableName;

    public:
        AllocateMemoryAction(
            const std::string&                                 addressVariableName,
            std::function<void(AllocatedMemoryActionBuilder&)> builderFunction
        )
            : _addressVariableName(addressVariableName) {
            AllocatedMemoryActionBuilder builder{*this};
            builderFunction(builder);
        }

        size_t GetByteCount() override {
            size_t byteCount = 0;
            for (auto& byteWriterAction : GetByteWriterActions())
                byteCount += byteWriterAction->GetByteCount();
            return byteCount;
        }

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto address = Memory::Allocate(GetByteCount());
            variables->Set<uintptr_t>(_addressVariableName, address);
            for (auto& byteWriterAction : this->GetByteWriterActions()) {
                variables->Set<uintptr_t>("__CURRENT_ADDRESS__", address);  // Lame sauce....
                byteWriterAction->Perform(variables);
                address += byteWriterAction->GetByteCount();
                variables->Set<uintptr_t>("__CURRENT_ADDRESS__", address);
            }
            variables->Set<uintptr_t>("__CURRENT_ADDRESS__", 0);  // maybe add Unset <---
        }
    };
}
