#include <Logging.h>
#include <Windows.h>

SetLogFilePath("Modding/Logs/ModdingFramework/modding_framework.lua.log");

extern "C" __declspec(dllexport) void Load() {
    Log("Load()");

    // Register as a Lua mod handler
}

extern "C" __declspec(dllexport) void Unload() { Log("Unload()"); }
