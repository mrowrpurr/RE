#include <Logging.h>
#include <Windows.h>

SetLogFilePath("Modding/Logs/ModdingFramework/modding_framework.lua.log");

// 2. GetSomething() to something which HAS the FUNCTION* to something and call it from somewhere

extern "C" __declspec(dllexport) void Load() { Log("Load()"); }
extern "C" __declspec(dllexport) void Unload() { Log("Unload()"); }
