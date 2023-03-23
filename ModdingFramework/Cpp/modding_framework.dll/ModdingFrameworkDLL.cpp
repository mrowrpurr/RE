#include <Injected_DLL.h>
#include <Logging.h>
#include <ModdingFramework/Runtime.h>

SetLogFilePath("Modding/Logs/ModdingFramework/modding_framework.dll.log");

DLL_Main {
    Log("Modding Framework DLL loaded");
    ModdingFramework::Runtime::Boot();
    Log("Ejecting Modding Framework DLL");
    EjectDLL();
}
