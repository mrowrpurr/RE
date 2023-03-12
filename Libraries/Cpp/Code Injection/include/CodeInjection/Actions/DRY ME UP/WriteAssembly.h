#pragma once

#include <Memory/MemoryWriter.h>
#include <StatefulApp/Action.h>
#include <stdint.h>
#include <xbyak/xbyak.h>

#include <functional>
#include <memory>
#include <vector>

using namespace Xbyak::util;

namespace CodeInjection {
    class WriteAssemblyAction : public StatefulApp::Action {
        std::function<void(Xbyak::CodeGenerator&)> _xbyakGeneratorFunction;
        uintptr_t                                  _address         = 0;
        std::string                                _outVariableName = "";

    public:
        WriteAssemblyAction(
            std::function<void(Xbyak::CodeGenerator&)> xbyakGeneratorFunction,
            uintptr_t address = 0, std::string outVariableName = ""
        )
            : _xbyakGeneratorFunction(xbyakGeneratorFunction),
              _address(address),
              _outVariableName(outVariableName) {}

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            Xbyak::CodeGenerator codeGenerator;
            _xbyakGeneratorFunction(codeGenerator);
            auto byteArray = codeGenerator.getCode();
            auto bytes     = std::vector<uint8_t>(byteArray, byteArray + codeGenerator.getSize());
            if (!_outVariableName.empty()) {
                variables->Set<std::vector<uint8_t>>(_outVariableName, bytes);
            } else if (_address != 0) {
                Memory::MemoryWriter{_address}.WriteBytes(bytes);
            } else {
                auto address = variables->Get<uintptr_t>("address");
                if (address != 0) Memory::MemoryWriter{address}.WriteBytes(bytes);
            }
        }
    };
}
