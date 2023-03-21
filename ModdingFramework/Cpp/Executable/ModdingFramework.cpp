#include <DLL_Injector.h>
#include <Logging.h>
#include <Serialization.h>
#include <Windows.h>

#include <iostream>

SetLogFilePath("modding_framework.loader.log");

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // TODO: make this not suck (don't directly use std::any)
    auto config = any_cast<std::unordered_map<std::string, std::any>>(
        Serialization::LoadFile("modding_framework.ini")["Modding Framework"]
    );
    auto game = any_cast<std::string>(config["game"]);

    if (DLL_Injector::Util::IsProcessRunning(game))
        DLL_Injector::InjectDLL(game, "modding_framework.dll");

    // if (GameIsRunning)
    //     InjectDll();
    // else {
    //      RunGameSuspended();
    //     InjectDll();
    // }

    return 0;
}
