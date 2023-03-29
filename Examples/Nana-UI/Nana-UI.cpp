#include <nana/gui.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/slider.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/widgets/textbox.hpp>

int main() {
    using namespace nana;

    form fm{API::make_center(500, 300)};
    fm.caption("Nana GUI Sample");

    tabbar<std::string> tab(fm);
    tab.push_back("Form");
    tab.push_back("Controls");

    panel<true> form_panel(fm);
    panel<true> controls_panel(fm);

    // Form layout
    place form_place{form_panel};
    form_place.div("vert <labels max=20 gap=10><inputs max=30 gap=10>");

    label   name_label{form_panel, "Name:"};
    textbox name_box{form_panel};

    label   age_label{form_panel, "Age:"};
    textbox age_box{form_panel};

    form_place["labels"] << name_label << age_label;
    form_place["inputs"] << name_box << age_box;

    form_place.collocate();

    // Controls layout
    place controls_place{controls_panel};
    controls_place.div("vert <sliders gap=5 max=30><radios gap=5 max=30><checkboxes gap=5 max=30>");

    label  slider_label{controls_panel, "Slider:"};
    slider slider_ctrl{controls_panel};

    label       radio_label{controls_panel, "Radio Group:"};
    radio_group radio_grp;
    checkbox    radio1{controls_panel, "Option 1"};
    checkbox    radio2{controls_panel, "Option 2"};
    radio_grp.add(radio1);
    radio_grp.add(radio2);

    label    checkbox_label{controls_panel, "Checkbox:"};
    checkbox checkbox_ctrl{controls_panel, "Enable"};

    controls_place["sliders"] << slider_label << slider_ctrl;
    controls_place["radios"] << radio_label << radio1 << radio2;
    controls_place["checkboxes"] << checkbox_label << checkbox_ctrl;

    controls_place.collocate();

    // Tab events
    tab.events().activated([&](const arg_tabbar<std::string>& bar) {
        if (bar.item_pos == 0) {
            form_panel.show();
            controls_panel.hide();
        } else {
            form_panel.hide();
            controls_panel.show();
        }
        return 1;
    });

    // Layout for the main form
    place main_place{fm};
    main_place.div("vert <tab weight=30><panel margin=10>");
    main_place["tab"] << tab;
    main_place["panel"].fasten(form_panel).fasten(controls_panel);
    // main_place["panel"] << form_panel << controls_panel;
    main_place.collocate();

    // controls_panel.hide();
    tab.activated(0);
    fm.show();

    exec();
    return 0;
}