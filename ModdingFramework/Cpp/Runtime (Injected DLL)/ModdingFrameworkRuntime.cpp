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

    // Call the void "CallMeMaybe" function in the DLL
    auto callMeMaybe = (void (*)())GetProcAddress(dllHandle, "CallMeMaybe");

    callMeMaybe();

    EjectDLL();
}
