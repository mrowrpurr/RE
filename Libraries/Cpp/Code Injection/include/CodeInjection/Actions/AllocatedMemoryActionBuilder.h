#pragma once

#include <stdint.h>

#include "CodeInjection/Actions/ByteWriterActionGroup.h"
#include "CodeInjection/Actions/WriteRawBytesAction.h"

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
    };
}
