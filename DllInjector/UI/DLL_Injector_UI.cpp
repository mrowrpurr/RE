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

//////////////

// #include <Windows.h>
// // ^ require Windows.h first

// #include <TlHelp32.h>

// #include <format>
// #include <iostream>

// DWORD GetProcId(const char* procName) {
//     DWORD  procId = 0;
//     HANDLE hSnap  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//     if (hSnap != INVALID_HANDLE_VALUE) {
//         PROCESSENTRY32 procEntry;
//         procEntry.dwSize = sizeof(procEntry);
//         if (Process32First(hSnap, &procEntry)) {
//             do {
//                 if (!_stricmp(procEntry.szExeFile, procName)) {
//                     procId = procEntry.th32ProcessID;
//                     break;
//                 }
//             } while (Process32Next(hSnap, &procEntry));
//         }
//     }
//     CloseHandle(hSnap);
//     return procId;
// }

// int main() {
//     std::cout << "main()" << std::endl;

//     // update to be the name of your process

// }
