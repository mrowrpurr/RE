#include <ButtonsApp.h>
#include <DLLInjection/FindSignature.h>
#include <DLLInjection/InjectedDLL.h>

void OnDllInjection() {
    auto address = DLLInjection::FindSignture(
        L"falloutwHR.exe", 0x10000,
        "\x89\x50\x04\x8B\x06\x89\x58\x28\x8B\x06\xC7\x40\x08\x00\x00\x00\x00\x8B\x06\xC7\x40\x0C\x00\x00\x00\x00",
        "xxxxxxxxxxxxxxxxxxxxxxxxxx"
    );

    ButtonsApp::Run([&](ButtonsApp& app) {
        app.SetTitle("Select Hooks");
        app.SetText(std::format("The found address is: 0x{:X}", address));
        app.SetButtonHeight(50);
        app.SetHeight(500);
        app.SetWidth(500);
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
    DLLInjection::EjectDLL();
}
