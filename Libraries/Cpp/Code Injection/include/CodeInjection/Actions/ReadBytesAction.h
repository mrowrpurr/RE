#pragma once

#include <Memory.h>
#include <StatefulApp.h>
#include <stdint.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace CodeInjection {
    class ReadBytesAction : public StatefulApp::Action {
        std::string _inputAddressVariableName;
        std::string _outputBytesVariableName;
        size_t      _byteCount;

    public:
        ReadBytesAction(
            const std::string& inputAddressVariableName, const std::string& outputBytesVariableName,
            size_t byteCount
        )
            : _inputAddressVariableName(inputAddressVariableName),
              _outputBytesVariableName(outputBytesVariableName),
              _byteCount(byteCount) {}

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto address = variables->Get<Memory::MemoryAddress>(_inputAddressVariableName);
            if (address.IsNull()) throw std::runtime_error("ReadBytesAction: Address is 0");
            auto bytes = Memory::MemoryReader{address}.Read(_byteCount);
            variables->Set(_outputBytesVariableName, bytes);
        }
    };
}
