#pragma once

#include <Logging.h>
#include <Memory.h>
#include <stdint.h>
#include <xbyak/xbyak.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "CodeInjection/Actions/ByteWriterActionBase.h"

// TODO - figure out how to mark as protected or not!

namespace CodeInjection {
    class WriteRawAssemblyAction : public ByteWriterActionBase {
        std::function<void(Xbyak::CodeGenerator&)> _xbyakGeneratorFunction;

    public:
        WriteRawAssemblyAction(std::function<void(Xbyak::CodeGenerator&)> xbyakGeneratorFunction)
            : _xbyakGeneratorFunction(xbyakGeneratorFunction) {}

        std::vector<uint8_t> GenerateBytes() {
            Xbyak::CodeGenerator codeGenerator;
            _xbyakGeneratorFunction(codeGenerator);
            auto byteArray = codeGenerator.getCode();
            return std::vector<uint8_t>(byteArray, byteArray + codeGenerator.getSize());
        }

        size_t GetByteCount() override { return GenerateBytes().size(); }

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            auto address = variables->Get<uintptr_t>("__CURRENT_ADDRESS__");
            auto bytes   = GenerateBytes();
            Log("Writing {} bytes to address {:x}", bytes.size(), address);
            if (address == 0) throw std::runtime_error("WriteRawAssemblyAction: Address is 0");
            Memory::MemoryWriter{address}.Protect().WriteBytes(bytes);
        }
    };
}
