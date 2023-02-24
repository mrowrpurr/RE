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

    uint32_t* item1Quantity = reinterpret_cast<uint32_t*>(player.GetREPlayer()->inventoryPtr + 0x4);
    Print("HOW MANY OF ITEM ONE???? {}", *item1Quantity);

    // auto* item = player.GetInventoryItem(0);
    // if (item) {
    //     Print("ITEM ptr: {}", item->ptr);
    //     Print("ITEM qty: {}", item->quantity);
    // }
}
