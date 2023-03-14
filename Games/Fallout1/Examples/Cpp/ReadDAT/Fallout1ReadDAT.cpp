#include <DatFile.h>
#include <DatFileItem.h>

#include <iostream>

using namespace DatUnpacker;

void ToLower(std::string& str) {
    for (auto& c : str) c = tolower(c);
}

int main() {
    auto datFile = DatFile{"D:\\GOG\\Games\\Fallout\\MASTER.DAT"};
    datFile.version();
    for (auto* item : *datFile.items()) {
        auto name = item->name();
        ToLower(name);
        if (name.ends_with("pro_item.msg") && name.contains("english")) {
            std::cout << item->name() << std::endl;
            std::cout << item->data() << std::endl;
        }
    }
    return 0;
}
