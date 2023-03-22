#include <Logging.h>
#include <Windows.h>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define __CURRENT_HMODULE ((HMODULE)&__ImageBase)

SetLogFilePath("Modding/Logs/MyFirstCppMod.log");

extern "C" __declspec(dllexport) void Load() {
    //
    Log("Load()");
}
extern "C" __declspec(dllexport) void Unload() {
    Log("Unload()");
    FreeLibrary(__CURRENT_HMODULE);
}
