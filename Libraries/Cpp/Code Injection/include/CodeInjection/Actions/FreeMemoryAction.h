#pragma once

#include <Memory.h>
#include <StatefulApp.h>
#include <stdint.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace CodeInjection {
    class FreeMemoryAction : public StatefulApp::Action {
        std::string _addressVariableName;

    public:
        FreeMemoryAction(const std::string& addressVariableName)
            : _addressVariableName(addressVariableName) {}

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto address = variables->Get<Memory::MemoryAddress>(_addressVariableName);
            if (address == 0) throw std::runtime_error("FreeMemoryAction: Address is 0");
            Memory::Free(address);
        }
    };
}
