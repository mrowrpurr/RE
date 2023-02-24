#pragma once

#include <format>
#include <iostream>
#include <string_view>


template <class... Args>
void Print(const std::string_view text, Args&&... args) {
    auto message = std::vformat(text, std::make_format_args(args...));
    std::cout << message << std::endl;
}