#pragma once

#include <StringFormatting.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))
