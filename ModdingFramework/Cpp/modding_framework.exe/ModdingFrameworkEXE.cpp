#include <DLL_Injector.h>
#include <Logging.h>
#include <Serialization.h>
#include <Windows.h>

#include <filesystem>
#include <iostream>

// Set this based on the modding_framework.ini file
// Use MessageBoxA to show errors before the logger is initialized
SetLogFilePath("Modding/Logs/ModdingFramework/modding_framework.exe.log");

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Log("Modding Framework EXE started");

    auto config  = Serialization::LoadFile("modding_framework.ini")["Modding Framework"];
    auto game    = config.Get("game");
    auto dllPath = std::filesystem::path("modding_framework.dll");
    if (!std::filesystem::exists(dllPath)) {
        Log("DLL '{}' does not exist, exiting...", dllPath.string());
        return 1;
    }

    if (DLL_Injector::Util::IsProcessRunning(game)) {
        Log("Game '{}' is running, injecting DLL...", game);
        DLL_Injector::InjectDLL(game, "modding_framework.dll");
    } else {
        Log("Game '{}' is not running, starting it... [or, okay, we *will* later]", game);
    }

    return 0;
}
