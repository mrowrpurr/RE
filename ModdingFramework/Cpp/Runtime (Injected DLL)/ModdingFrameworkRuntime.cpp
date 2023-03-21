#include <Injected_DLL.h>
#include <Logging.h>

SetLogFilePath("ModdingFrameworkRuntime.log");

DLL_Main {
    Log("Hello from ModdingFrameworkRuntime.dll");

    auto dllPath =
        "C:/Code/mrowrpurr/Retro-RE-Playground/build/debug/Examples/DLLsToLoad/Cpp/LoadThisDLL1/"
        "LoadThisDLL1.dll";

    // Load the DLL using LoadLibrary
    auto dllHandle = LoadLibraryA(dllPath);

    auto callMeMaybe = (uint32_t(*)(uint32_t))GetProcAddress(dllHandle, "CallMeMaybe");

    auto result = callMeMaybe(420);

    Log("Result from calling CallMeMaybe() in the loaded DLL is: {}", result);

    EjectDLL();
}
