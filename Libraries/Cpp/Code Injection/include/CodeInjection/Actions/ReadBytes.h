#pragma once

#include <Memory/MemoryWriter.h>
#include <StatefulApp/Action.h>
#include <stdint.h>

#include <memory>
#include <vector>

namespace CodeInjection {
    class ReadBytesAction : public StatefulApp::Action {
        std::string _outVariableName;
        uintptr_t   _address;
        size_t      _size;

    public:
        ReadBytesAction(const std::string& outVariableName, uintptr_t address, size_t size)
            : _outVariableName(outVariableName), _address(address), _size(size) {}

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto address = _address;
            if (address == 0) address = variables->Get<uintptr_t>("address");
            if (address == 0) throw std::runtime_error("ReadBytesAction: Address is 0");
            auto bytes = Memory::MemoryReader{address}.Read(_size).GetBytes();
            variables->Set<std::vector<uint8_t>>(_outVariableName, bytes);
        }
    };
}
