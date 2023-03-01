#include <format>
#include <functional>
#include <iostream>
#include <memory>
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <optional>
#include <string_view>
#include <vector>

class ButtonsApp {
    nana::form                                 _form;
    nana::place                                _place;
    nana::label                                _outputLabel;
    std::vector<std::string>                   _buttonInitialText;
    std::vector<std::function<std::string()>>  _buttonClickCallbacks;
    std::vector<std::unique_ptr<nana::button>> _buttons;

    ButtonsApp() : _place(_form), _outputLabel(_form, "") {}
    ~ButtonsApp()                            = default;
    ButtonsApp(const ButtonsApp&)            = delete;
    ButtonsApp(ButtonsApp&&)                 = delete;
    ButtonsApp& operator=(const ButtonsApp&) = delete;
    ButtonsApp& operator=(ButtonsApp&&)      = delete;

public:
    static ButtonsApp& GetSingleton() {
        static ButtonsApp singleton;
        return singleton;
    }

    void SetTitle(const std::string& title) { _form.caption(title); }

    void AddButton(const std::string& text, std::function<std::string()> callback) {
        _buttonInitialText.push_back(text);
        _buttonClickCallbacks.push_back(callback);
    }

    void Print(const std::string& text) { _outputLabel.caption(_outputLabel.caption() + "\n" + text); }
    void Clear() { _outputLabel.caption(""); }

    void Run() {
        nana::label lblTopPadding(_form, "");
        std::string arrangement{"5"};
        for (auto& _ : _buttonInitialText) arrangement += ",25";
        arrangement += ",10000";
        _place.div(std::format("<><width=90% <vertical fields gap=10 arrange=[{}]>><>", arrangement));
        _place.field("fields") << lblTopPadding;

        for (size_t i = 0; i < _buttonInitialText.size(); i++) {
            auto* btn = new nana::button(_form, _buttonInitialText[i]);
            _buttons.push_back(std::unique_ptr<nana::button>(btn));
            auto callback = _buttonClickCallbacks[i];
            btn->events().click([btn, callback]() {
                try {
                    btn->caption(callback());
                } catch (const std::exception& e) {
                    btn->caption(std::string("Exception: ") + e.what());
                } catch (...) {
                    btn->caption("Unknown exception");
                }
            });
            _place.field("fields") << *btn;
        }

        _place.field("fields") << _outputLabel;
        _place.collocate();
        _form.show();
        nana::exec();
    }
};

template <class... Args>
void Print(const std::string_view text, Args&&... args) {
    auto message = std::vformat(text, std::make_format_args(args...));
    ButtonsApp::GetSingleton().Print(message);
    std::cout << message << std::endl;
}
void ClearOutput() { ButtonsApp::GetSingleton().Clear(); }

int main() {
    auto& app = ButtonsApp::GetSingleton();
    app.SetTitle("Injected .dll - UI");
    app.AddButton("dsfs", []() {
        Print("1111");
        return "Hello ONE!";
    });
    app.AddButton("sdfsdfsfsdfds", []() {
        ClearOutput();
        return "Hello TWO!";
    });
    app.Run();
}
