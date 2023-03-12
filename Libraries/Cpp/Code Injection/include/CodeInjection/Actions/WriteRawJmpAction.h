#pragma once

#include <Logging.h>
#include <Memory.h>
#include <StatefulApp.h>
#include <stdint.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "CodeInjection/Actions/ByteWriterActionBase.h"

namespace CodeInjection {
    class WriteRawJmpAction : public ByteWriterActionBase {
        std::string _jumpToAddressVariableName = "";

    public:
        WriteRawJmpAction(const std::string& jumpToAddressVariableName)
            : _jumpToAddressVariableName(jumpToAddressVariableName) {}

        size_t GetByteCount() override { return 5; }

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto jumpToAddress = variables->Get<Memory::MemoryAddress>(_jumpToAddressVariableName);
            if (jumpToAddress.IsNull()) throw std::runtime_error("WriteRawJmpAction: Address is 0");

            auto address = variables->Get<uintptr_t>("__CURRENT_ADDRESS__");
            Log("Writing JMP to address {:x} to address {:x}", jumpToAddress.GetAddress(), address);
            if (address == 0) throw std::runtime_error("WriteRawJmpAction: Address is 0");

            auto relativeAddress = jumpToAddress - address - 5;  // 5 is the JMP address
            Memory::MemoryWriter{address}.WriteByte(0xE9);
            Memory::MemoryWriter{address + 1}.WriteDword(relativeAddress.GetAddress());
        }
    };
}
