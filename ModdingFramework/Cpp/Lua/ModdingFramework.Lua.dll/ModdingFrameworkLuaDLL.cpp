#include <Logging.h>
#include <Windows.h>

struct DumbStruct {
    const char* text;
    uint32_t    number;
};

class SlightlyIntelligentClass {
    uint32_t neatNumber;

public:
    virtual uint32_t GetNumber() const;
};

SetLogFilePath("Modding/Logs/ModdingFramework/modding_framework.lua.log");

// 1. Pass an object WITH A FUNCTION* to Load() and call it from Load()
//
// 2. GetSomething() to something which HAS the FUNCTION* to something and call it from somewhere
//

extern "C" __declspec(dllexport) void Load(SlightlyIntelligentClass* slightlyIntelligentClass) {
    Log("Load()");

    Log("SlightlyIntelligentClass::GetNumber() = {}", slightlyIntelligentClass->GetNumber());
}

extern "C" __declspec(dllexport) void Unload() {
    //
    Log("Unload()");
}
