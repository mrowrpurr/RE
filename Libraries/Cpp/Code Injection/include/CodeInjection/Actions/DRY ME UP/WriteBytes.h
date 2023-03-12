#pragma once

#include <Memory/MemoryWriter.h>
#include <StatefulApp/Action.h>
#include <stdint.h>

#include <memory>
#include <string>
#include <vector>

#include "CodeInjection/Actions/ByteWriterActionBase.h"

namespace CodeInjection {
    class WriteBytesAction : public ByteWriterActionBase {
        std::vector<uint8_t> _bytes;
        std::string          _bytesVariableName = "";

    public:
        WriteBytesAction(std::vector<uint8_t> bytes) : _bytes(bytes) {}

        size_t GetByteCount() override { return _bytes.size(); }

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto address = variables->Get<uintptr_t>("address");
            if (address == 0) throw std::runtime_error("WriteBytesAction: Address is 0");
            if (_bytesVariableName != "")
                _bytes = variables->Get<std::vector<uint8_t>>(_bytesVariableName);
            Memory::MemoryWriter{address}.WriteBytes(_bytes);
        }
    };
}
