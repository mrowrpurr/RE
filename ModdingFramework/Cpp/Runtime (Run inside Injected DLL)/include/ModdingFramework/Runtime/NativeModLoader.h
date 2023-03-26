#pragma once

#include <Logging.h>
#include <StringFormatting.h>

#include <filesystem>

#include "Mod.h"

namespace ModdingFramework::Runtime::NativeModLoader {
    // Lazy for now...
    std::unordered_map<std::string, HMODULE> _dllModules;

    bool Load(const Mod& mod) {
        Log("Loading native mod: {}", mod.GetName());

        auto dllPath = mod.GetPath() / mod.GetSource();
        if (!std::filesystem::exists(dllPath)) {
            Log("Native mod DLL not found: {}", dllPath.string());
            return false;
        }

        auto dll = LoadLibraryA(dllPath.string().c_str());
        if (!dll) {
            Log("Failed to load native mod DLL: {}", dllPath.string());
            return false;
        }

        _dllModules[mod.GetName()] = dll;

        // auto initModdingFrameworkFn = (void (*)(Types::ModdingFrameworkType*)
        // )GetProcAddress(dll, "__MODDING_FRAMEWORK_INIT__");

        // if (!initModdingFrameworkFn) {
        //     Log("Failed to find __MODDING_FRAMEWORK_INIT__ function in native mod DLL: {}",
        //         dllPath.string());
        //     return false;
        // }

        // try {
        //     initModdingFrameworkFn(
        //         nullptr
        //         // &ModdingFramework::Runtime::ModdingFrameworkTypeImpl::GetSingleton()
        //     );
        // } catch (const std::exception& e) {
        //     Log("Failed to call __MODDING_FRAMEWORK_INIT__ in native mod DLL: {}", e.what());
        //     return false;
        // } catch (...) {
        //     Log("Failed to call __MODDING_FRAMEWORK_INIT__ in native mod DLL: Unknown error");
        //     return false;
        // }

        auto loadMod = (void (*)())GetProcAddress(dll, "Load");
        if (!loadMod) {
            Log("Failed to find Load function in native mod DLL: {}", dllPath.string());
            return false;
        }

        try {
            loadMod();
            Log("Loaded native mod DLL: {}", dllPath.string());
            return true;
        } catch (const std::exception& e) {
            Log("Failed to load native mod DLL: {}", e.what());
        } catch (...) {
            Log("Failed to load native mod DLL: Unknown error");
        }
        return false;
    }

    bool Unload(const Mod& mod) {
        Log("Unloading native mod: {}", mod.GetName());

        auto dllPath = mod.GetPath() / mod.GetSource();
        if (!std::filesystem::exists(dllPath)) {
            Log("Native mod DLL not found: {}", dllPath.string());
            return false;
        }

        auto dll = _dllModules[mod.GetName()];
        if (!dll) {
            Log("Native mod DLL not loaded: {}", dllPath.string());
            return false;
        }

        auto unloadMod = (void (*)())GetProcAddress(dll, "Unload");
        if (!unloadMod) {
            Log("Failed to find Unload function in native mod DLL: {}", dllPath.string());
            return false;
        }

        try {
            unloadMod();
            Log("Unloaded native mod DLL: {}", dllPath.string());
            FreeLibrary(dll);
            _dllModules.erase(mod.GetName());
            Log("FreeLibrary DLL: {}", dllPath.string());
            return true;
        } catch (const std::exception& e) {
            Log("Failed to unload native mod DLL: {}", e.what());
        } catch (...) {
            Log("Failed to unload native mod DLL: Unknown error");
        }
        return false;
    }
}