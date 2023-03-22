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

// auto dllPath =
//     "C:/Code/mrowrpurr/Retro-RE-Playground/build/debug/Examples/DLLsToLoad/Cpp/LoadThisDLL1/"
//     "LoadThisDLL1.dll";
// auto dllHandle   = LoadLibraryA(dllPath);
// auto callMeMaybe = (uint32_t(*)(uint32_t))GetProcAddress(dllHandle, "CallMeMaybe");
// auto result      = callMeMaybe(420);
// Log("Result from calling CallMeMaybe() in the loaded DLL is: {}", result);

// auto rustDllPath =
//     "C:/Code/mrowrpurr/Retro-RE-Playground/Examples/HelloRust/target/i686-pc-windows-msvc/"
//     "debug/hello_rust.dll";
// auto rustDllHandle   = LoadLibraryA(rustDllPath);
// auto rustCallMeMaybe = (uint32_t(*)(uint32_t))GetProcAddress(rustDllHandle, "CallMeMaybe");
// auto rustResult      = rustCallMeMaybe(420);
// Log("Result from calling CallMeMaybe() in the loaded Rust DLL is: {}", rustResult);

// void RunUI() {
//     UserInterface::Run([](UIApp& app) {
//         app.SetTitle("Modding Framework");
//         app.SetHeight(300);
//         app.SetWidth(500);
//         app.SetButtonHeight(50);
//         app.ShowOutputTextBox();
//         // Display one button per plugin (and display if it is native or Lua etc)
//         for (auto& plugin : PluginManager::GetPlugins()) {
//             app.AddButton(string_format("Load {}", plugin.GetName()), [&plugin]() {
//                 if (plugin.IsLoaded()) {
//                     plugin.Unload();
//                     app.ChangeButtonText(string_format("Load {}", plugin.GetName());
//                 } else {
//                     plugin.Load();
//                     app.ChangeButtonText(string_format("Unload {}", plugin.GetName());
//                 }
//             });
//         }
//     });
// }