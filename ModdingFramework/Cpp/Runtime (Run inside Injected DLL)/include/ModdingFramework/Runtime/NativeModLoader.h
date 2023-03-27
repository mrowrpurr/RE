#pragma once

#include <Logging.h>
#include <ModdingFramework/IMod.h>
#include <ModdingFramework/IModLoader.h>
#include <StringFormatting.h>

#include <filesystem>

namespace ModdingFramework::Runtime {

    class NativeModLoader : public IModLoader {
    public:
        static constexpr auto DLL_HMODULE_DATA_KEY = "DLL_HMODULE";

        bool LoadMod(IMod* mod) override {
            if (!mod) {
                Log("Mod is null");
                return false;
            }
            Log("Loading native mod: {}", mod->GetName());

            auto modFolder = std::filesystem::path(mod->GetFolder());
            auto dllPath   = modFolder / mod->GetSource();
            if (!std::filesystem::exists(dllPath)) {
                Log("Native mod DLL not found: {}", dllPath.string());
                return false;
            }

            auto dllHMODULE = LoadLibraryA(dllPath.string().c_str());
            if (!dllHMODULE) {
                Log("Failed to load native mod DLL: {}", dllPath.string());
                return false;
            }

            mod->SetData(DLL_HMODULE_DATA_KEY, dllHMODULE, 0);

            auto loadMod = (void (*)())GetProcAddress(dllHMODULE, "Load");
            if (!loadMod) {
                Log("Failed to find Load function in native mod DLL: {}", dllPath.string());
                return false;
            }

            try {
                loadMod();
                Log("Loaded native mod DLL: {}", dllPath.string());
                mod->SetLoaded(true);
                return true;
            } catch (const std::exception& e) {
                Log("Failed to load native mod DLL: {}", e.what());
            } catch (...) {
                Log("Failed to load native mod DLL: Unknown error");
            }
        }

        bool UnloadMod(IMod* mod) override {
            if (!mod) {
                Log("Mod is null");
                return false;
            }
            Log("Unloading native mod: {}", mod->GetName());

            auto modFolder = std::filesystem::path(mod->GetFolder());
            auto dllPath   = modFolder / mod->GetSource();
            if (!std::filesystem::exists(dllPath)) {
                Log("Native mod DLL not found: {}", dllPath.string());
                return false;
            }

            auto dllHMODULE = (HMODULE)mod->GetData(DLL_HMODULE_DATA_KEY);
            if (!dllHMODULE) {
                Log("Failed to unload native mod DLL: DLL_HMODULE data is null");
                return false;
            }

            auto unloadMod = (void (*)())GetProcAddress(dllHMODULE, "Unload");
            if (!unloadMod) {
                Log("Failed to find Unload function in native mod DLL: {}", dllPath.string());
                return false;
            }

            try {
                unloadMod();
                Log("Unload() called on native mod DLL: {}\nFreeing...", dllPath.string());
                FreeLibrary(dllHMODULE);
                Log("FreeLibrary() called on native mod DLL: {}", dllPath.string());
                mod->RemoveDataKey(DLL_HMODULE_DATA_KEY);
                Log("Unloaded native mod DLL: {}", dllPath.string());
                mod->SetLoaded(false);
                return true;
            } catch (const std::exception& e) {
                Log("Failed to unload native mod DLL: {}", e.what());
            } catch (...) {
                Log("Failed to unload native mod DLL: Unknown error");
            }
        }
    };
}
