#include <Logging.h>
#include <Windows.h>

#include <cstdint>
#include <thread>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define __CURRENT_HMODULE ((HMODULE)&__ImageBase)

SetLogFilePath("CallMeMaybe.log");

extern "C" __declspec(dllexport) void Load() {}
extern "C" __declspec(dllexport) void Unload() { FreeLibrary(__CURRENT_HMODULE); }
extern "C" __declspec(dllexport) uint32_t CallMeMaybe(uint32_t x) { return (x * 100) + 69; }
