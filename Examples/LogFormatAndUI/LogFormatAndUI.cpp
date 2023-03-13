#include <Logging.h>
#include <UserInterface.h>
#include <StringFormatting.h>

UI_Main {
    UserInterface::Run([](auto& app) {
        app.SetTitle("Just an example").SetHeight(500).SetWidth(300).ShowOutputTextBox();
        app.AddButton("Click me", [&]() { app.ChangeButtonText("Clicked"); });
        app.AddButton("Clear Output", [&]() { app.ClearOutput(); });
        app.AddButton("Append Output", [&]() { app.AppendOutput("Hello"); });
    });
}
