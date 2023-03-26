#pragma once

#include <UserInterface.h>

namespace ModdingFramework::Runtime {

    class UI {
    public:
        void static Run() {
            UserInterface::Run([](UIApp& app) {
                app.SetTitle("Hello from the injected .dll!");
                app.SetButtonHeight(50);
                app.SetHeight(500);
                app.SetWidth(500);

                // auto& registry = System::GetSystem().GetRegistry();
                // registry.ForEachMod([&app](const Mod& mod) {
                //     std::string buttonText =
                //         System::GetSystem().GetLoader().IsLoaded(mod) ? "Unload " : "Load ";
                //     buttonText += mod.GetName();

                //     app.AddButton(buttonText, [mod, &app]() {
                //         auto& loader = System::GetSystem().GetLoader();
                //         if (loader.IsLoaded(mod)) {
                //             Log("Unloading mod: {}", mod.GetName());
                //             loader.Unload(mod);
                //             if (loader.IsLoaded(mod)) {
                //                 Log("Failed to unload mod: {}", mod.GetName());
                //                 app.ChangeButtonText("Failed to unload " + mod.GetName());
                //             } else {
                //                 Log("Unloaded mod: {}", mod.GetName());
                //                 app.ChangeButtonText("Load " + mod.GetName());
                //             }
                //         } else {
                //             loader.Load(mod);
                //             if (loader.IsLoaded(mod)) {
                //                 Log("Loaded mod: {}", mod.GetName());
                //                 app.ChangeButtonText("Unload " + mod.GetName());
                //             } else {
                //                 Log("Failed to load mod: {}", mod.GetName());
                //                 app.ChangeButtonText("Failed to load " + mod.GetName());
                //             }
                //         }
                //     });
                // });
            });
        }
    };
}