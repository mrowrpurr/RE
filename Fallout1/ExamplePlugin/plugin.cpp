#include <DllInjector/DllInjector.h>
#include <Fallout1.h>

#include "Print.h"

using namespace Fallout1;

void Injected_DLL_Main() {
    Fallout1::RE::MODULE_BASE = DllInjector::MODULE_BASE;

    auto& player = Fallout1::GetPlayer();

    Print("NAME: {}", player.GetName());
    Print("AGE: {}", player.GetAge());
    Print("INVENTORY COUNT: {}", player.GetInventoryCount());

    for (unsigned int i = 0; i < player.GetInventoryCount(); ++i) {
        auto item = player.GetInventoryItem(i);
        Print("ITEM QUANTITY: {}", item.quantity);
        Print("Item Pointer: {:x}", item.ptr);
    }
}
