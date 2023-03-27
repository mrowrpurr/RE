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
            });
        }
    };
}