#include <form_app.h>
#include <logging.h>
#include <string_format.h>

LogFile("log-format-ui-example.log");

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    FormApp::Run([](FormApp& app) {
        app.SetTitle("This is the title");
        app.AddButton("Click Me", [&]() {
            Log("You clicked the button");
            app.AppendOutput("Click!");
        });
    });
}
