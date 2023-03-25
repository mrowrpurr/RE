#pragma once

#include <Logging.h>
#include <StringFormatting.h>

#include "ModdingFramework/RegisterModTypeHandler.h"
#include "ModdingFrameworkTypeInstance.h"

/**
 * This file *should* be included by all mods.
 */

#define SetModName(mod_name) \
    SetLogFilePath(string_format("Modding/Logs/ModdingFramework/{}.log", mod_name));

#define OnLoad extern "C" __declspec(dllexport) void Load()
#define OnUnload extern "C" __declspec(dllexport) void Unload()

extern "C" __declspec(dllexport) void __MODDING_FRAMEWORK_INIT__(
    ModdingFramework::Types::ModdingFrameworkType* moddingFrameworkInstance
) {
    Log("ModdingFramework::SetModdingFrameworkPtr was called with a "
        "ModdingFramework::Types::ModdingFrameworkType*");
    if (moddingFrameworkInstance == nullptr) {
        Log("ModdingFramework::SetModdingFrameworkPtr was called with a nullptr");
    } else {
        Log("ModdingFramework::SetModdingFrameworkPtr was called with a NON-NULLPTR");
    }
    ModdingFramework::SetModdingFrameworkPtr(moddingFrameworkInstance);
}
