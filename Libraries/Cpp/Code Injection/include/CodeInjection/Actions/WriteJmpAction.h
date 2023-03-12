#pragma once

#include <Memory.h>
#include <StatefulApp.h>
#include <stdint.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace CodeInjection {
    class WriteJmpAction : public StatefulApp::Action {
        std::string _writeAtAddressVariableName = "";
        std::string _jumpToAddressVariableName  = "";

    public:
        WriteJmpAction(
            const std::string& writeAtAddressVariableName,
            const std::string& jumpToAddressVariableName
        )
            : _writeAtAddressVariableName(writeAtAddressVariableName),
              _jumpToAddressVariableName(jumpToAddressVariableName) {}

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto writeAtAddress =
                variables->Get<Memory::MemoryAddress>(_writeAtAddressVariableName);
            if (writeAtAddress.IsNull()) throw std::runtime_error("WriteJmpAction: Address is 0");

            auto jumpToAddress = variables->Get<Memory::MemoryAddress>(_jumpToAddressVariableName);
            if (jumpToAddress.IsNull()) throw std::runtime_error("WriteJmpAction: Address is 0");

            auto relativeAddress = jumpToAddress - writeAtAddress - 5;  // 5 is the JMP
            auto writer          = Memory::MemoryWriter{writeAtAddress}.Protect();
            writer.WriteByte(0xE9);
            writer.SetAddress(writeAtAddress.Offset(1));
            writer.WriteDword(relativeAddress.GetAddress());
        }
    };
}
