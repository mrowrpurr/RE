#include <Injected_DLL.h>
#include <Logging.h>
#include <ModdingFramework/Runtime.h>

// testing...
#include <Serialization.h>
#include <UserInterface.h>

SetLogFilePath("Modding/Logs/ModdingFramework/modding_framework.dll.log");

DLL_Main {
    Log("Modding Framework DLL loaded");
    ModdingFramework::Runtime::Boot();

    // TODO - move eject responsibilities to runtime
    Log("Ejecting Modding Framework DLL");
    EjectDLL();
}
