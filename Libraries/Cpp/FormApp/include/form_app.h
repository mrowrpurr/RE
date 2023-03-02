#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <vector>

class FormApp {
    static std::atomic_bool                    _isSetup;
    size_t                                     _buttonHeight{25};
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

    FormApp() : _place(_form), _outputLabel(_form, ""), _headerLabel(_form, "") {}
    ~FormApp()                         = default;
    FormApp(const FormApp&)            = delete;
    FormApp(FormApp&&)                 = delete;
    FormApp& operator=(const FormApp&) = delete;
    FormApp& operator=(FormApp&&)      = delete;

    void Resize() { _form.size({_width, _height + (_buttonInitialText.size() * _buttonHeight)}); }
    void RunApp() {
        if (_isRunning.exchange(true)) return;

        nana::label lblTopPadding(_form, "");

        std::string arrangement{"5"};
        if (!_headerLabel.caption().empty()) arrangement += "," + std::to_string(_buttonHeight);
        for (size_t i = 0; i < _buttonInitialText.size(); i++) arrangement += "," + std::to_string(_buttonHeight);
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
    static FormApp& GetSingleton() {
        static FormApp singleton;
        return singleton;
    }

public:
    static void Setup(std::function<void(FormApp& app)> callback) {
        if (_isSetup.exchange(true)) return;
        callback(GetSingleton());
    }
    static void Run(std::function<void(FormApp& app)> callback = [](auto&) {}) {
        auto& app = GetSingleton();
        callback(app);
        app.RunApp();
    }

    void SetTitle(const std::string& title) { _form.caption(title); }
    void SetText(const std::string& text) { _headerLabel.caption(text); }
    void SetButtonHeight(size_t height) { _buttonHeight = height; }

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

    void Close() { nana::API::exit_all(); }
};

std::atomic<bool> FormApp::_isSetup{false};