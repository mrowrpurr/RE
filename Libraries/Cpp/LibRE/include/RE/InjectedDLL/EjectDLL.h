#pragma once

#include "RE/InjectedDLL/Module.h"

namespace RE::InjectedDll {
    void EjectDLL() { FreeLibraryAndExitThread(InjectedIntoModule, 0); }
}
