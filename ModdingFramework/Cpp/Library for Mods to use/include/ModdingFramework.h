#pragma once

// #include <ModdingFramework.h>
//
// Only intended to be used by

// #define SetModName(mod_name) \
//     SetLogFilePath(string_format("Modding/Logs/ModdingFramework/{}.log", mod_name));

// #define OnUnload extern "C" __declspec(dllexport) void Unload()

// extern "C" __declspec(dllexport) void __MODDING_FRAMEWORK_INIT__(
//     ModdingFramework::Types::ModdingFrameworkType* moddingFrameworkInstance
// ) {
//     Log("ModdingFramework::SetModdingFrameworkPtr was called with a "
//         "ModdingFramework::Types::ModdingFrameworkType*");
//     if (moddingFrameworkInstance == nullptr) {
//         Log("ModdingFramework::SetModdingFrameworkPtr was called with a nullptr");
//     } else {
//         Log("ModdingFramework::SetModdingFrameworkPtr was called with a NON-NULLPTR");
//     }
//     ModdingFramework::SetModdingFrameworkPtr(moddingFrameworkInstance);
// }