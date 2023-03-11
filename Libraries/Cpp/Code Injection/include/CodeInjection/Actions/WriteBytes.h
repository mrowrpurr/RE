#pragma once

#include <Memory/MemoryWriter.h>
#include <StatefulApp/Action.h>
#include <stdint.h>

#include <memory>
#include <vector>


class WriteBytesAction : public StatefulApp::Action {
    std::vector<uint8_t> _bytes;

public:
    WriteBytesAction(std::vector<uint8_t> bytes) : _bytes(bytes) {}

    void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
        auto address = variables->Get<uintptr_t>("address");
        Memory::MemoryWriter{address}.Protect().WriteBytes(_bytes);
    }
};