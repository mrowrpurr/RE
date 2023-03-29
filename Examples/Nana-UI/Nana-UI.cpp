#include <nana/gui.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/slider.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/widgets/textbox.hpp>

int main() {
    using namespace nana;

    // Create the main form
    form fm{API::make_center(400, 300)};
    fm.caption("Nana GUI App");

    auto panel1 = panel<true>(fm);
    auto panel2 = panel<true>(fm);

    // Create the tab bar and tabs
    tabbar<std::string> tabs(fm, rectangle(10, 10, 380, 280));
    tabs.append("Form with Labels and Textboxes", panel1);
    tabs.append("Form with Sliders, Radio Buttons, and Checkboxes", panel2);

    label label1{panel1, "Name:"};
    label1.move(30, 20);
    textbox textbox1{panel1, rectangle(100, 20, 200, 20)};

    label label2{panel1, "Age:"};
    label2.move(30, 60);
    textbox textbox2{panel1, rectangle(100, 60, 200, 20)};

    // Second tab: Form with Sliders, Radio Buttons, and Checkboxes
    slider slider1{panel2, rectangle(30, 20, 200, 20)};
    slider slider2{panel2, rectangle(30, 60, 200, 20)};

    label label3{panel2, "Gender:"};
    label3.move(240, 20);
    radio_group gender_group;
    checkbox    male_radio{panel2, "Male"};
    gender_group.add(male_radio);
    male_radio.move(240, 40);

    checkbox female_radio{panel2, "Female"};
    gender_group.add(female_radio);
    female_radio.move(240, 60);

    checkbox check1{panel2, "Check 1"};
    check1.move(30, 100);
    checkbox check2{panel2, "Check 2"};
    check2.move(30, 130);

    // Show the form
    fm.show();

    // Run the event loop
    exec();
    return 0;
}