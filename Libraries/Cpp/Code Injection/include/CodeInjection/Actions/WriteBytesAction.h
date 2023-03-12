#pragma once

#include <Memory.h>
#include <StatefulApp.h>
#include <stdint.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace CodeInjection {
    class WriteBytesAction : public StatefulApp::Action {
        bool        _protectedBytes      = false;
        std::string _addressVariableName = "";
        std::string _bytesVariableName   = "";

    public:
        WriteBytesAction(
            const std::string& addressVariableName, const std::string& bytesVariableName
        )
            : _addressVariableName(addressVariableName), _bytesVariableName(bytesVariableName) {}

        WriteBytesAction Protected() {
            WriteBytesAction action{_addressVariableName, _bytesVariableName};
            action._protectedBytes = true;
            return action;
        }

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto address = variables->Get<Memory::MemoryAddress>(_addressVariableName);
            if (address.IsNull()) throw std::runtime_error("WriteBytesAction: Address is 0");
            auto bytes = variables->Get<Memory::Bytes>(_bytesVariableName);
            // if (_protectedBytes) {
            Memory::MemoryWriter{address}.Protect().WriteBytes(bytes);
        }
    };
}
