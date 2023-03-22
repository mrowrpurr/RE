#include <DLL_Injector.h>
#include <Logging.h>
#include <Serialization.h>
#include <Windows.h>

#include <iostream>

SetLogFilePath("Modding/Logs/ModdingFramework/modding_framework.exe.log");

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Log("Modding Framework EXE started");

    // TODO: make this not suck (don't directly use std::any)
    auto config = any_cast<std::unordered_map<std::string, std::any>>(
        Serialization::LoadFile("modding_framework.ini")["Modding Framework"]
    );
    auto game = any_cast<std::string>(config["game"]);

    if (DLL_Injector::Util::IsProcessRunning(game)) {
        Log("Game '{}' is running, injecting DLL...", game);
        DLL_Injector::InjectDLL(game, "modding_framework.dll");
    } else {
        Log("Game '{}' is not running, starting it... [or, okay, we *will* later]", game);
    }

    // if (GameIsRunning)
    //     InjectDll();
    // else {
    //      RunGameSuspended();
    //     InjectDll();
    // }

    return 0;
}
