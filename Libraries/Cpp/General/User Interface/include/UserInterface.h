#pragma once

#include "UserInterface/Application.h"
#include "UserInterface/Macros/UI_Main.h"

namespace UserInterface {
    void Run(std::function<void(Application& app)> callback = [](auto&) {}) { Application::Run(callback); }
    void Close() { Application::Current().Close(); }
}
