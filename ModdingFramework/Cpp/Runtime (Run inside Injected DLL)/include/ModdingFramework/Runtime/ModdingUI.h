#pragma once

#include <Logging.h>
#include <UserInterface.h>

#include "ModdingRuntime.h"

namespace ModdingFramework::Runtime {

    class ModdingUI {
    public:
        void static Run() {
            UserInterface::Run([](UIApp& app) {
                app.SetTitle("Hello from the injected .dll!");
                app.SetButtonHeight(50);
                app.SetHeight(500);
                app.SetWidth(500);

                auto& runtime  = ModdingRuntime::GetRuntime();
                auto& registry = runtime.GetRegistry();
                registry.ForEachMod([&app](const std::shared_ptr<Mod>& mod) {
                    app.AddButton(mod->GetName(), [&mod]() {
                        Log("Clicked mod {}", mod->GetName());
                    });
                });
            });
        }
    };
}