#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

int main() {
    using namespace nana;

    form  fm;
    place layout(fm);

    button btn1(fm, "Button 1");
    button btn2(fm, "Button 2");
    label  lblHeader(fm, "Injected .dll");
    label  lblOutput(fm, "Output");
    label  output(
        fm,
        "fdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\ndjsklfjsklfjdskljfklsdjflksdjkfdjslkfjsljfklds"
         "jfkldsjfkldjsfkdjsklfjdlksjfksjfdklsjfklsjdfklsjfkljsdlkfjsdkljflksjflkdjsfklds kjdfld jslkfsdlk flkj sdlfk "
         "jsjf sld jflkdsj flk dsjlfk jsdlkfj dslkf jdslkf jdlksfj slfj dslk "
         "jfdslfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nd"
         "jsklfjsklfjdskljfklsdjflksdjkfdjslkfjsljfkldsjfkldsjfkldjsfkdjsklfjdlksjfksjfdklsjfklsjdfklsjfkljsdlkfjsdkljfl"
         "ksjflkdjsfklds kjdfld jslkfsdlk flkj sdlfk jsjf sld jflkdsj flk dsjlfk jsdlkfj dslkf jdslkf jdlksfj slfj dslk "
         "jfdslfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nd"
         "jsklfjsklfjdskljfklsdjflksdjkfdjslkfjsljfkldsjfkldsjfkldjsfkdjsklfjdlksjfksjfdklsjfklsjdfklsjfkljsdlkfjsdkljfl"
         "ksjflkdjsfklds kjdfld jslkfsdlk flkj sdlfk jsjf sld jflkdsj flk dsjlfk jsdlkfj dslkf jdslkf jdlksfj slfj dslk "
         "jfdslfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nd"
         "jsklfjsklfjdskljfklsdjflksdjkfdjslkfjsljfkldsjfkldsjfkldjsfkdjsklfjdlksjfksjfdklsjfklsjdfklsjfkljsdlkfjsdkljfl"
         "ksjflkdjsfklds kjdfld jslkfsdlk flkj sdlfk jsjf sld jflkdsj flk dsjlfk jsdlkfj dslkf jdslkf jdlksfj slfj dslk "
         "jfdslfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nd"
         "jsklfjsklfjdskljfklsdjflksdjkfdjslkfjsljfkldsjfkldsjfkldjsfkdjsklfjdlksjfksjfdklsjfklsjdfklsjfkljsdlkfjsdkljfl"
         "ksjflkdjsfklds kjdfld jslkfsdlk flkj sdlfk jsjf sld jflkdsj flk dsjlfk jsdlkfj dslkf jdslkf jdlksfj slfj dslk "
         "jfdslfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nd"
         "jsklfjsklfjdskljfklsdjflksdjkfdjslkfjsljfkldsjfkldsjfkldjsfkdjsklfjdlksjfksjfdklsjfklsjdfklsjfkljsdlkfjsdkljfl"
         "ksjflkdjsfklds kjdfld jslkfsdlk flkj sdlfk jsjf sld jflkdsj flk dsjlfk jsdlkfj dslkf jdslkf jdlksfj slfj dslk "
         "jfdslfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\nd"
         "jsklfjsklfjdskljfklsdjflksdjkfdjslkfjsljfkldsjfkldsjfkldjsfkdjsklfjdlksjfksjfdklsjfklsjdfklsjfkljsdlkfjsdkljfl"
         "ksjflkdjsfklds kjdfld jslkfsdlk flkj sdlfk jsjf sld jflkdsj flk dsjlfk jsdlkfj dslkf jdslkf jdlksfj slfj dslk "
         "jfdslfdjdls\nfdjdls\nfdjdls\nfdjdls\nfdjdls\n"
    );

    layout.field("fields") << lblHeader << btn1 << btn2 << lblOutput << output;
    layout.div("<><width=90% <vertical fields gap=10 arrange=[25,25,25,25,10000]>><>");

    layout.collocate();
    fm.show();
    exec();
}
