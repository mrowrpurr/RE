#pragma once

#include <Logging.h>
#include <Serialization.h>

#include <filesystem>

namespace ModdingFramework::PluginManager {

    // Hardcode this stuff for now...
    // TODO - actually read from the .ini
    constexpr auto FolderWithNativeMods = "Modding/Mods/Native";

    void LoadAndUnloadMod(const std::string& iniFileName) {
        auto iniFilePath = std::filesystem::path(FolderWithNativeMods) / iniFileName;
        auto config      = any_cast<std::unordered_map<std::string, std::any>>(
            Serialization::LoadFile(iniFilePath.string())["Mod"]
        );
        auto dllFilename = any_cast<std::string>(config["dll"]);
        auto dllPath     = std::filesystem::path(FolderWithNativeMods) / dllFilename;

        // Load dll with LoadLibrary
        Log("Loading mod DLL: {}", dllPath.string());
        auto dllHandle = LoadLibrary(dllPath.string().c_str());
        if (dllHandle == nullptr) {
            Log("Failed to load mod DLL: {}", dllPath.string());
            return;
        }

        // Get the address of the void "Load" function which takes no arguments
        Log("Getting address of Load function");
        auto loadFunction = GetProcAddress(dllHandle, "Load");
        if (loadFunction == nullptr) {
            Log("Failed to get address of Load function");
            return;
        }

        // Call the "Load" function
        Log("Calling Load function");
        auto loadFunctionVoid = reinterpret_cast<void (*)()>(loadFunction);
        loadFunctionVoid();

        // Get the address of the void "Unload" function which takes no arguments
        Log("Getting address of Unload function");
        auto unloadFunction = GetProcAddress(dllHandle, "Unload");
        if (unloadFunction == nullptr) {
            Log("Failed to get address of Unload function");
            return;
        }

        // Call the "Unload" function
        Log("Calling Unload function");
        auto unloadFunctionVoid = reinterpret_cast<void (*)()>(unloadFunction);
        unloadFunctionVoid();
    }

    // Lookup and log all of the NATIVE mods that we find!
    // TODO - actually use the Native Mod Manager to load the plugins!
    void SearchForMods() {
        Log("Searching for mods...");

        // Log current working directory
        Log("Current working directory: {}", std::filesystem::current_path().string());

        // Return if FolderWithNativeMods doesn't exist
        if (!std::filesystem::exists(FolderWithNativeMods)) {
            Log("Folder with native mods doesn't exist: {}", FolderWithNativeMods);
            return;
        }

        // Find all .ini files in FolderWithNativeMods
        for (const auto& entry : std::filesystem::directory_iterator(FolderWithNativeMods)) {
            if (entry.path().extension() == ".ini") {
                Log("Found mod: {}", entry.path().filename().string().c_str());
                LoadAndUnloadMod(entry.path().filename().string());
            }
        }
    }

    void Boot() {
        Log("Booting Plugin Manager");
        SearchForMods();
    }
}
