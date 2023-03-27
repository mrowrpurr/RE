#pragma once

#include <Logging.h>
#include <StringFormatting.h>
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

                auto& registry = ModdingRuntime::GetRuntime().GetRegistry();
                registry.ForEachMod([&app](const std::shared_ptr<Mod>& mod) {
                    auto buttonText = std::string{mod->GetName()};
                    if (mod->IsLoaded()) buttonText = "Unload " + buttonText;
                    else buttonText = "Load " + buttonText;

                    app.AddButton(mod->GetName(), [&mod, &app]() {
                        auto& loaders = ModdingRuntime::GetRuntime().GetModLoaders();
                        if (mod->IsLoaded()) {
                            loaders.UnloadMod(mod.get());
                            app.ChangeButtonText(string_format("Load {}", mod->GetName()));
                        } else {
                            loaders.LoadMod(mod.get());
                            app.ChangeButtonText(string_format("Unload {}", mod->GetName()));
                        }
                    });
                });
            });
        }
    };
}