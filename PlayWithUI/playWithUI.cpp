#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

using namespace nana;

int main() {
    form fm;
    fm.caption("FORM CAPTION");
    fm.bgcolor(colors::white);

    label lbl(fm, rectangle(10, 10, 100, 20));
    lbl.caption("LABEL CAPTION");

    button btn(fm, rectangle(10, 40, 100, 20));
    btn.caption("BUTTON CAPTION");
    btn.events().click([&fm, &lbl] { lbl.caption("BUTTON CLICKED"); });

    fm.show();
    exec();
}