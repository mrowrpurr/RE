#include <iostream>
#include <Msg/File.h>
#include <Msg/Message.h>
#include <Dat/File.h>

using namespace libfalltergeist;

int main() {
    auto pathToMasterDAT = "D:/GOG/Games/Fallout/MASTER.DAT";
    // auto pathToMasterDAT = "D:/GOG/Games/Fallout 2/MASTER.DAT";
    
    auto datFile = Dat::File(pathToMasterDAT);
    auto* itemsMsgFile = static_cast<Msg::File*>(datFile.item("text/english/game/pro_item.msg"));

    auto itemName = itemsMsgFile->message(4000)->text();
    auto itemDescription = itemsMsgFile->message(4001)->text();

    std::cout << "Item name: " << itemName << std::endl;
    std::cout << "Item description: " << itemDescription << std::endl;

    return 0;
}