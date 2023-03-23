#pragma once

#include <ModdingFramework/Runtime/System.h>
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
                for (auto& [_, mod] : System::GetSystem().GetRegistry().GetMods())
                    app.AddButton(mod.GetName(), []() {
                        //     //
                    });
            });
        }
    };
}