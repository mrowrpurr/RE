#include <Logging.h>

SetLogFilePath("Modding/Logs/LogInventory.Cpp.log");

extern "C" __declspec(dllexport) void Load() { Log("Load()"); }
extern "C" __declspec(dllexport) void Unload() { Log("Unload()"); }
