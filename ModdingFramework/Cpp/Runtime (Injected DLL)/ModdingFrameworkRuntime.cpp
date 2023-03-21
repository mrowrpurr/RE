#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <UserInterface/Macros/Output.h>

SetLogFilePath("modding_framework.log");

DLL_Main {
    UserInterface::Run([](UIApp& app) {
        app.SetTitle("Modding Framework");
        app.SetHeight(300);
        app.SetWidth(500);
        app.SetButtonHeight(50);
        app.ShowOutputTextBox();
        app.AddButton("Click Me", []() { Output("you clicked the button"); });
    });
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