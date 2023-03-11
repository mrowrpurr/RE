#pragma once

#include <Memory/MemoryWriter.h>
#include <StatefulApp/Action.h>
#include <stdint.h>

#include <memory>
#include <vector>

namespace CodeInjection {
    class WriteProtectedBytesAction : public StatefulApp::Action {
        std::vector<uint8_t> _bytes;

    public:
        WriteProtectedBytesAction(std::vector<uint8_t> bytes) : _bytes(bytes) {}

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto address = variables->Get<uintptr_t>("address");
            if (address == 0) throw std::runtime_error("WriteBytesAction: Address is 0");
            Memory::MemoryWriter{address}.Protect().WriteBytes(_bytes);
        }
    };
}
