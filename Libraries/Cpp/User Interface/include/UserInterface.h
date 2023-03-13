#pragma once

#include "UserInterface/Application.h"
#include "UserInterface/Macros/UI_Main.h"

namespace UserInterface {
    Application& App() { return Application::Current(); }
    void         Run(std::function<void(Application& app)> callback = [](auto&) {}) { Application::Run(callback); }
    void         Close() { Application::Current().Close(); }
}
