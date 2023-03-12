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
    class WriteRawBytesAction : public ByteWriterActionBase {
        Memory::Bytes _bytes;

    public:
        WriteRawBytesAction(const Memory::Bytes& bytes) : _bytes(bytes) {}
        WriteRawBytesAction(const std::vector<uint8_t>& bytes) : _bytes(bytes) {}

        size_t GetByteCount() override {
            //
            return _bytes.GetSize();
        }

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto address = variables->Get<uintptr_t>("__CURRENT_ADDRESS__");
            Log("Writing {} bytes to address {:x}", _bytes.ToString(), address);
            if (address == 0) throw std::runtime_error("WriteRawBytesAction: Address is 0");
            Memory::MemoryWriter{address}.WriteBytes(_bytes);
        }
    };
}
