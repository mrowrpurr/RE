#pragma once

#include <Memory/MemoryWriter.h>
#include <StatefulApp/Action.h>
#include <stdint.h>

#include <memory>
#include <vector>

namespace CodeInjection {
    class WriteProtectedBytesByVarAction : public StatefulApp::Action {
        std::string _bytesVariableName = "";

    public:
        WriteProtectedBytesByVarAction(const std::string& bytesVariableName)
            : _bytesVariableName(bytesVariableName) {}

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto address = variables->Get<uintptr_t>("address");
            if (address == 0) throw std::runtime_error("WriteBytesAction: Address is 0");
            auto bytes = variables->Get<std::vector<uint8_t>>(_bytesVariableName);
            Memory::MemoryWriter{address}.Protect().WriteBytes(bytes);
        }
    };
}
