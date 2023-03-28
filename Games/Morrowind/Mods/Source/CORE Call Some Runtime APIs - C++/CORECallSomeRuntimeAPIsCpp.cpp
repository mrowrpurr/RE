#include <ModdingFramework/IModdingRuntime.h>
// #include <ModdingFramework/CoreMod.h>
#include <Logging.h>

SetLogFilePath("Modding/Logs/CORE-CallSomethingRuntimeAPIS-Cpp.log");

extern "C" __declspec(dllexport) void Load(ModdingFramework::IModdingRuntime* runtime) {
    //
    Log("Ok. We're going to use this mod to demonstrate how to call Runtime APIs.");
    //
    auto gameExe = runtime->GetRuntimeConfig()->GetGameExecutable();
    Log("Game executable: {}", gameExe);
    //
    auto modFolder = runtime->GetRuntimeConfig()->GetModsFolderPath();
    Log("Mod folder: {}", modFolder);
    //
    auto modCount = runtime->GetRegistry()->GetModCount();
    Log("Mod count: {}", modCount);
    //
    for (auto i = 0; i < modCount; i++) {
        auto mod = runtime->GetRegistry()->GetMod(i);
        Log("Mod {} name: {}", i, mod->GetName());
    }
    //
}

extern "C" __declspec(dllexport) void Unload() {}
