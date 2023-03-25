#pragma once

#include <StringFormatting.h>

/**
 * This file *should* be included by all mods.
 */

#define SetModName(mod_name) \
    SetLogFilePath(string_format("Modding/Logs/ModdingFramework/{}.log", mod_name));

#define OnLoad extern "C" __declspec(dllexport) void Load()
#define OnUnload extern "C" __declspec(dllexport) void Unload()
