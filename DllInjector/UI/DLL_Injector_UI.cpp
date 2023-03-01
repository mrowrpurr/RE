#include <ButtonsApp.h>
#include <DLLInjection/DLLInjector.h>

constexpr auto Fallout1_EXE = L"falloutwHR.exe";
constexpr auto Fallout1_DLL =
    "C:/Code/mrowrpurr/Retro-RE-Playground/build/debug/Fallout1/ExamplePlugin/Fallout1.ExamplePlugin.dll";

constexpr auto Vampire_EXE = L"Vampire.exe";
constexpr auto Vampire_DLL = "REBUILD ME!";

void Run() {
    ButtonsApp::Run([](ButtonsApp& app) {
        app.SetTitle("Choose DLL to Inject");
        app.SetWidth(600);
        app.SetHeight(50);
        app.AddButton("Fallout 1", [&]() { DLLInjection::InjectDLL(Fallout1_EXE, Fallout1_DLL); });
        app.AddButton("Vampire the Masquerade: Bloodlines", []() {
            DLLInjection::InjectDLL(Vampire_EXE, Vampire_DLL);
        });
    });
}

int        main() { Run(); }
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) { Run(); }
