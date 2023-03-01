#include <ButtonsApp.h>
#include <DLLInjection/InjectedDLL.h>

#include <chrono>
#include <format>
#include <iostream>
#include <thread>

void OnDllInjection() {
    ButtonsApp::Run([&](ButtonsApp& app) {
        app.SetTitle("Select Hooks");
        app.SetButtonHeight(50);
        app.SetHeight(500);
        app.SetWidth(500);
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
    DLLInjection::EjectDLL();
}
