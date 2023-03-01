#include <atomic>
#include <functional>
#include <memory>
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <vector>

/** Example
int main() {
    ButtonsApp::Setup([](ButtonsApp& app) {
        app.SetTitle("Injected .dll - UI");
        app.SetText("Hello, friends!");
        app.AddButton("Rename Button", [&]() { app.ChangeButtonText("NEW BUTTON TEXT!"); });
        app.AddButton("Print Output", [&]() { app.AppendOutput("Hello from button one!"); });
        app.AddButton("Change Title", [&]() { app.SetTitle("NEW TITLE"); });
        app.AddButton("Change Text", [&]() { app.SetText("NEW TEXT"); });
        app.AddButton("Kaboom", [&]() { throw "Kaboom!"; });
        app.AddButton("Change Size", [&]() {
            app.SetHeight(800);
            app.SetWidth(800);
        });
        app.AddButton("Rename Different Button", [&]() { app.ChangeButtonText("NEW !!! TEXT!"); });
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
    });
    ButtonsApp::Run();
}
 */

class ButtonsApp {
    static std::atomic_bool                    _isSetup;
    size_t                                     _height{300};
    size_t                                     _width{250};
    std::atomic_bool                           _isRunning{false};
    nana::form                                 _form;
    nana::place                                _place;
    nana::label                                _outputLabel;
    nana::label                                _headerLabel;
    std::vector<std::string>                   _buttonInitialText;
    std::vector<std::function<void()>>         _buttonClickCallbacks;
    std::vector<std::shared_ptr<nana::button>> _buttons;
    std::shared_ptr<nana::button>              _currentButtonBeingClicked{nullptr};

    ButtonsApp() : _place(_form), _outputLabel(_form, ""), _headerLabel(_form, "") {}
    ~ButtonsApp()                            = default;
    ButtonsApp(const ButtonsApp&)            = delete;
    ButtonsApp(ButtonsApp&&)                 = delete;
    ButtonsApp& operator=(const ButtonsApp&) = delete;
    ButtonsApp& operator=(ButtonsApp&&)      = delete;

    void Resize() { _form.size({_width, _height + (_buttonInitialText.size() * 25)}); }
    void RunApp() {
        if (_isRunning.exchange(true)) return;

        nana::label lblTopPadding(_form, "");

        std::string arrangement{"5"};
        if (!_headerLabel.caption().empty()) arrangement += ",25";
        for (auto& _ : _buttonInitialText) arrangement += ",25";
        arrangement += ",10000";

        _place.div("<><width=90% <vertical fields gap=10 arrange=[" + arrangement + "]>><>");

        _place.field("fields") << lblTopPadding;
        if (!_headerLabel.caption().empty()) _place.field("fields") << _headerLabel;

        for (size_t i = 0; i < _buttonInitialText.size(); i++) {
            auto* btn    = new nana::button(_form, _buttonInitialText[i]);
            auto  btnPtr = std::shared_ptr<nana::button>(btn);
            _buttons.push_back(btnPtr);
            auto callback = _buttonClickCallbacks[i];
            btn->events().click([&, btn, btnPtr, callback]() {
                try {
                    _currentButtonBeingClicked = btnPtr;
                    callback();
                } catch (const std::exception& e) {
                    _outputLabel.caption(_outputLabel.caption() + "\n" + "Exception: " + e.what());
                } catch (const char* e) {
                    _outputLabel.caption(_outputLabel.caption() + "\n" + "Exception: " + e);
                } catch (...) {
                    _outputLabel.caption(_outputLabel.caption() + "\n" + "Unknown exception");
                }
            });
            _place.field("fields") << *btn;
        }

        _place.field("fields") << _outputLabel;
        Resize();
        _place.collocate();
        _form.show();
        nana::exec();
    }
    static ButtonsApp& GetSingleton() {
        static ButtonsApp singleton;
        return singleton;
    }

public:
    static void Setup(std::function<void(ButtonsApp& app)> callback) {
        if (_isSetup.exchange(true)) return;
        callback(GetSingleton());
    }
    static void Run(std::function<void(ButtonsApp& app)> callback = [](auto&){}) {
        auto& app = GetSingleton();
        callback(app);
        app.RunApp();
    }

    void SetTitle(const std::string& title) { _form.caption(title); }
    void SetText(const std::string& text) { _headerLabel.caption(text); }

    void AddButton(const std::string& text, std::function<void()> callback) {
        _buttonInitialText.push_back(text);
        _buttonClickCallbacks.push_back(callback);
    }

    void ChangeButtonText(const std::string& text) {
        if (_currentButtonBeingClicked) _currentButtonBeingClicked->caption(text);
    }

    void AppendOutput(const std::string& text) { _outputLabel.caption(_outputLabel.caption() + "\n" + text); }
    void SetOutput(const std::string& text) { _outputLabel.caption(text); }
    void ClearOutput() { _outputLabel.caption(""); }
    void SetHeight(short height) {
        _height = height;
        Resize();
    }
    void SetWidth(short width) {
        _width = width;
        Resize();
    }
};

std::atomic<bool> ButtonsApp::_isSetup{false};
