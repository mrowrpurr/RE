#pragma once

#include <Windows.h>

#include <format>
#include <string_view>


template <class... Args>
void MsgBox(const std::string_view text, Args&&... args) {
    auto message = std::vformat(text, std::make_format_args(args...));
    MessageBoxA(0, message.c_str(), "Our Sweet Fallout Injected DLL", MB_OK);
}