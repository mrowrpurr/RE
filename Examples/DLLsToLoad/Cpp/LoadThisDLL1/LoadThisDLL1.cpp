#include <Logging.h>

SetLogFilePath("LoadThisDLL1.log");

// 1. No Args
// 2. An arg!
// 3. A return value!

extern "C" __declspec(dllexport) void CallMeMaybe() {
    int me = 0x69;
    //
    Log("Call me, maybe!");
}
