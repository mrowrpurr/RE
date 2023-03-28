#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <nana/gui.hpp>
#include <nana/gui/detail/bedrock.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/slider.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <string>
#include <vector>

namespace UserInterface {
    class Application {
        bool                                       _showOutputTextBox{false};
        unsigned int                               _buttonHeight{25};
        unsigned int                               _height{300};
        unsigned int                               _width{250};
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

        void Resize() {
            _form.size(
                {_width,
                 _height + (static_cast<unsigned int>(_buttonInitialText.size()) * _buttonHeight)}
            );
        }
        void RunApp() {
            using namespace nana;
            // Create the main form
            form fm{API::make_center(300, 300)};
            fm.caption("Nana C++ Library - Tabbed Application");

            // Create the tabbar
            tabbar<std::string> tabs(fm);
            tabs.push_back("Tab 1");
            tabs.push_back("Tab 2");
            tabs.push_back("Tab 3");

            // Create the panel for each tab
            panel<false> tab1(fm), tab2(fm), tab3(fm);
            place        layout(fm);
            layout.div("vert <tabs><<tab1><tab2><tab3>>");

            checkbox chk_butts(tab1, "Butts");
            chk_butts.events().checked([](const arg_checkbox& arg) {
                // Event handler for checkbox
            });

            label   lbl_foo(tab2, "Foo");
            textbox txt_foo(tab2);
            label   lbl_bar(tab2, "Bar");
            textbox txt_bar(tab2);

            // Tab 3 - Slider
            slider sldr(tab3, rectangle(point(20, 20), size(200, 20)));
            sldr.value(69);
            sldr.events().value_changed([](const arg_slider& arg) {
                // Event handler for slider
            });

            // Set tab visibility and bind to the tabbar
            layout.field("tab1") << tab1;
            layout.field("tab2") << tab2;
            layout.field("tab3") << tab3;
            layout.field("tabs") << tabs;
            layout.collocate();

            tabs.events().activated([&](const arg_tabbar<std::string>&) {
                unsigned index = tabs.activated();

                tab1.hide();
                tab2.hide();
                tab3.hide();

                if (index == 0) tab1.show();
                else if (index == 1) tab2.show();
                else if (index == 2) tab3.show();
            });

            // Show the first tab by default
            tabs.activated(0);
            // tab1.show();

            // Run the main loop
            fm.show();
            exec();
        }
        void RunAppXXX() {
            if (_isRunning.exchange(true)) return;

            nana::label lblTopPadding(_form, "");

            std::string arrangement{"5,10"};
            if (!_headerLabel.caption().empty()) arrangement += "," + std::to_string(_buttonHeight);
            for (size_t i = 0; i < _buttonInitialText.size(); i++)
                arrangement += "," + std::to_string(_buttonHeight);
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
                        _outputTextBox.caption(
                            _outputTextBox.caption() + "\n" + "Exception: " + e.what()
                        );
                    } catch (const char* e) {
                        _outputTextBox.caption(_outputTextBox.caption() + "\n" + "Exception: " + e);
                    } catch (...) {
                        _outputTextBox.caption(
                            _outputTextBox.caption() + "\n" + "Unknown exception"
                        );
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

        void Close() {
            _form.close();
            nana::API::exit_all();
        }
    };
}
