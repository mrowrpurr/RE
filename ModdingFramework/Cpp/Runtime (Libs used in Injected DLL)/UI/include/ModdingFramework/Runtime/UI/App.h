#pragma once

#include <ModdingFramework/Runtime/System.h>
#include <StringFormatting.h>
#include <UserInterface.h>

namespace ModdingFramework::Runtime::UI {
    class App {
    public:
        void static RunUI() {
            UserInterface::Run([](UIApp& app) {
                app.SetTitle("Hello from the injected .dll!");
                app.SetButtonHeight(50);
                app.SetHeight(500);
                app.SetWidth(500);

                auto system   = System::GetSystem();
                auto registry = system.GetRegistry();
                auto loader   = system.GetLoader();

                for (auto& [_, mod] : System::GetSystem().GetRegistry().GetMods()) {
                    std::string buttonText = loader.IsLoaded(mod) ? "Unload " : "Load ";
                    buttonText += mod.GetName();

                    app.AddButton(buttonText, [&]() {
                        if (loader.IsLoaded(mod)) {
                            loader.Unload(mod);
                            if (loader.IsLoaded(mod)) {
                                app.ChangeButtonText("Failed to unload " + mod.GetName());
                            } else {
                                app.ChangeButtonText("Load " + mod.GetName());
                            }
                        } else {
                            loader.Load(mod);
                            if (loader.IsLoaded(mod)) {
                                app.ChangeButtonText("Unload " + mod.GetName());
                            } else {
                                app.ChangeButtonText("Failed to load " + mod.GetName());
                            }
                        }
                    });
                }
            });
        }
    };
}