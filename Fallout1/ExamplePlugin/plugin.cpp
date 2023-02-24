#include <DllInjector/DllInjector.h>
#include <Fallout1.h>

#include "Print.h"

using namespace Fallout1;

void Injected_DLL_Main() {
    Fallout1::RE::MODULE_BASE = DllInjector::MODULE_BASE;

    auto& player = Fallout1::GetPlayer();

    Print("NAME: {}", player.GetName());
    Print("AGE: {}", player.GetAge());
    auto count = player.GetInventoryCount();
    Print("INVENTORY COUNT: {}", count);

    auto items = player.GetInventoryItems();
    for (auto& item : items) {
        Print("ITEM QUANTITY: {}", item.quantity);
        Print("ITEM PID: {}", item.item->prototypeID);
    }
}
