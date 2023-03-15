#pragma once

#include <xbyak/xbyak.h>

#include <functional>
#include <vector>

// using namespace Xbyak::util;

namespace Assembly {

    typedef Xbyak::CodeGenerator& Code;

    std::vector<uint8_t> GetBytes(std::function<void(Xbyak::CodeGenerator&)> generator) {
        Xbyak::CodeGenerator code;
        generator(code);
        auto byteArray = code.getCode();
        return std::vector<uint8_t>(byteArray, byteArray + code.getSize());
    }
}
