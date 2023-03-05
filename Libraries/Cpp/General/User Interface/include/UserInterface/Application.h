#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <vector>

namespace UserInterface {
    class Application {
        bool                                       _showOutputTextBox{false};
        size_t                                     _buttonHeight{25};
        size_t                                     _height{300};
        size_t                                     _width{250};
        std::atomic_bool                           _isRunning{false};
        nana::form                                 _form;
        nana::place                                _place;
        nana::textbox                              _outputTextBox;
        nana::label                                _headerLabel;
        std::vector<std::string>                   _buttonInitialText;
        std::vector<std::function<void()>>         _buttonClickCallbacks;
        std::vector<std::shared_ptr<nana::button>> _buttons;
        std::shared_ptr<nana::button>              _currentButtonBeingClicked{nullptr};

        Application() : _place(_form), _outputTextBox(_form, ""), _headerLabel(_form, "") {}
        ~Application()                             = default;
        Application(const Application&)            = delete;
        Application(Application&&)                 = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&)      = delete;

        void Resize() { _form.size({_width, _height + (_buttonInitialText.size() * _buttonHeight)}); }
        void RunApp() {
            if (_isRunning.exchange(true)) return;

            nana::label lblTopPadding(_form, "");

            std::string arrangement{"5"};
            if (!_headerLabel.caption().empty()) arrangement += "," + std::to_string(_buttonHeight);
            for (size_t i = 0; i < _buttonInitialText.size(); i++) arrangement += "," + std::to_string(_buttonHeight);
            if (_showOutputTextBox) arrangement += ",10000";

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
                        _outputTextBox.caption(_outputTextBox.caption() + "\n" + "Exception: " + e.what());
                    } catch (const char* e) {
                        _outputTextBox.caption(_outputTextBox.caption() + "\n" + "Exception: " + e);
                    } catch (...) {
                        _outputTextBox.caption(_outputTextBox.caption() + "\n" + "Unknown exception");
                    }
                });
                _place.field("fields") << *btn;
            }

            if (_showOutputTextBox) _place.field("fields") << _outputTextBox;
            Resize();
            _place.collocate();
            _form.show();
            nana::exec();
        }

    public:
        static Application& Current() {
            static Application singleton;
            return singleton;
        }
        static void Run(std::function<void(Application& app)> callback = [](auto&) {}) {
            auto& app = Current();
            callback(app);
            app.RunApp();
        }

        Application& SetTitle(const std::string& title) {
            _form.caption(title);
            return *this;
        }
        Application& SetText(const std::string& text) {
            _headerLabel.caption(text);
            return *this;
        }
        Application& SetButtonHeight(size_t height) {
            _buttonHeight = height;
            return *this;
        }
        Application& AddButton(const std::string& text, std::function<void()> callback) {
            _buttonInitialText.push_back(text);
            _buttonClickCallbacks.push_back(callback);
            return *this;
        }
        Application& ChangeButtonText(const std::string& text) {
            if (_currentButtonBeingClicked) _currentButtonBeingClicked->caption(text);
            return *this;
        }
        Application& AppendOutput(const std::string& text) {
            _outputTextBox.caption(_outputTextBox.caption() + "\n" + text);
            return *this;
        }
        Application& SetOutput(const std::string& text) {
            _outputTextBox.caption(text);
            return *this;
        }
        Application& ClearOutput() {
            _outputTextBox.caption("");
            return *this;
        }
        Application& SetHeight(short height) {
            _height = height;
            Resize();
            return *this;
        }
        Application& ShowOutputTextBox(bool show = true) {
            _showOutputTextBox = show;
            return *this;
        }
        Application& SetWidth(short width) {
            _width = width;
            Resize();
            return *this;
        }

        void Close() { nana::API::exit_all(); }
    };
}
