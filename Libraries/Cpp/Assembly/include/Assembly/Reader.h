#pragma once

#include <Zydis/Zydis.h>

#include <string>
#include <vector>

namespace Assembly {

    enum class AssemblyType { x86, x64 };

    std::vector<std::string> DisassembleBytes(
        AssemblyType assemblyType, const std::vector<uint8_t>& bytes, uint64_t address = 0x0
    ) {
        ZydisDecoder decoder;
        switch (assemblyType) {
            case AssemblyType::x86:
                ZydisDecoderInit(
                    &decoder, ZYDIS_MACHINE_MODE_LONG_COMPAT_32, ZYDIS_ADDRESS_WIDTH_32
                );
                break;
            case AssemblyType::x64:
                ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);
                break;
        }

        ZydisFormatter formatter;
        ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

        std::vector<std::string> disassembled_bytes;
        ZydisDecodedInstruction  instruction;
        size_t                   offset = 0;
        while (ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(
            &decoder, bytes.data() + offset, bytes.size() - offset, &instruction
        ))) {
            char buffer[256];
            ZydisFormatterFormatInstruction(
                &formatter, &instruction, buffer, sizeof(buffer), address + offset
            );
            disassembled_bytes.push_back(buffer);
            offset += instruction.length;
        }
        return disassembled_bytes;
    }

    std::vector<std::string> Disassemble86(
        const std::vector<uint8_t>& bytes, uint64_t address = 0x0
    ) {
        return DisassembleBytes(AssemblyType::x86, bytes, address);
    }

    std::vector<std::string> Disassemble64(
        const std::vector<uint8_t>& bytes, uint64_t address = 0x0
    ) {
        return DisassembleBytes(AssemblyType::x64, bytes, address);
    }
}
