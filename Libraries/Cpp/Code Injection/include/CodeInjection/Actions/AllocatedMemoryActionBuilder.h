#pragma once

#include <stdint.h>

#include "CodeInjection/Actions/ByteWriterActionGroup.h"
#include "CodeInjection/Actions/WriteRawAssemblyAction.h"
#include "CodeInjection/Actions/WriteRawBytesAction.h"
#include "CodeInjection/Actions/WriteRawJmpAction.h"

namespace CodeInjection {

    class AllocatedMemoryActionBuilder {
        ByteWriterActionGroup& _byteWriterActionGroup;

    public:
        AllocatedMemoryActionBuilder(ByteWriterActionGroup& byteWriterActionGroup)
            : _byteWriterActionGroup(byteWriterActionGroup) {}

        AllocatedMemoryActionBuilder& WriteBytes(const std::vector<uint8_t>& bytes) {
            _byteWriterActionGroup.AddAction(WriteRawBytesAction{bytes});
            return *this;
        }

        AllocatedMemoryActionBuilder& WriteAssembly(
            const std::function<void(Xbyak::CodeGenerator&)>& assembly
        ) {
            _byteWriterActionGroup.AddAction(WriteRawAssemblyAction{assembly});
            return *this;
        }

        AllocatedMemoryActionBuilder& WriteJmp(const std::string& jumpToAddressVariableName) {
            _byteWriterActionGroup.AddAction(WriteRawJmpAction{jumpToAddressVariableName});
            return *this;
        }
    };
}
