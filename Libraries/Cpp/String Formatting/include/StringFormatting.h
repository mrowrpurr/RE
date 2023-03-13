#pragma once

#ifdef USE_FMT_FOR_FORMATTING
    #include <fmt/format.h>
    #define string_format(...) fmt::format(__VA_ARGS__)
#else
    #include <format>
    #define string_format(...) std::format(__VA_ARGS__)
#endif
