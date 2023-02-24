#include <DllInjector/DllInjector.h>
#include <Fallout1.h>

#include "Print.h"

void Injected_DLL_Main() {
    Fallout1::RE::MODULE_BASE = DllInjector::MODULE_BASE;

    auto& player = Fallout1::GetPlayer();
    Print("The player's age is {}", player.GetAge());

    player.SetAge(22);
    Print("The player's age is {}", player.GetAge());
}
