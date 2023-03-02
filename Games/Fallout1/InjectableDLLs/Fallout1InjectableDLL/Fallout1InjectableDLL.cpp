#include <RE/Helpers/FindByteSignatureAddress.h>
#include <RE/InjectedDLL.h>
#include <form_app.h>

void OnDllInjection() {
    auto address = RE::Helpers::FindByteSignatureAddress(
        L"falloutwHR.exe", 0x10000,
        "\x89\x50\x04\x8B\x06\x89\x58\x28\x8B\x06\xC7\x40\x08\x00\x00\x00\x00\x8B\x06\xC7\x40\x0C\x00\x00\x00\x00",
        "xxxxxxxxxxxxxxxxxxxxxxxxxx"
    );
    FormApp::Run([&](FormApp& app) {
        app.SetTitle("Select Hooks");
        app.SetText(std::format("The found address is: 0x{:X}", address));
        app.SetButtonHeight(50);
        app.SetHeight(500);
        app.SetWidth(500);
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
    RE::InjectedDLL::EjectDLL();
}
