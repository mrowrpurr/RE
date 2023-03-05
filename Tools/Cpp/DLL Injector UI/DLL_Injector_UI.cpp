#include <RE/DLLInjection.h>
#include <form_app.h>

constexpr auto Fallout1_EXE = L"falloutwHR.exe";
constexpr auto Fallout1_DLL =
    "C:/Code/mrowrpurr/Retro-RE-Playground/build/debug/Games/Fallout1/InjectableDLLs/Fallout1InjectableDLL/"
    "Fallout1InjectableDLL.dll";

constexpr auto Vampire_EXE = L"Vampire.exe";
constexpr auto Vampire_DLL = "REBUILD ME!";

void Run() {
    FormApp::Run([](FormApp& app) {
        app.SetTitle("Choose DLL to Inject");
        app.SetWidth(600);
        app.SetHeight(50);
        app.AddButton("Fallout 1", [&]() { RE::DLLInjection::InjectDLL(Fallout1_EXE, Fallout1_DLL); });
        app.AddButton("Vampire the Masquerade: Bloodlines", []() {
            RE::DLLInjection::InjectDLL(Vampire_EXE, Vampire_DLL);
        });
    });
}

int        main() { Run(); }
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) { Run(); }
