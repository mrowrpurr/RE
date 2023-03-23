#include <Logging.h>
#include <Windows.h>

SetLogFilePath("Modding/Logs/MyFirstCppMod.log");

struct Whatever {};

Whatever whatever;

extern "C" __declspec(dllexport) void Load() {
    Log("Load()");
    Log("The address of whatever is {:x}", reinterpret_cast<uintptr_t>(&whatever));
}
extern "C" __declspec(dllexport) void Unload() { Log("Unload()"); }
