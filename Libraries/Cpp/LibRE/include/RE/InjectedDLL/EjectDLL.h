#pragma once

#include "RE/InjectedDLL/Module.h"

namespace RE::InjectedDLL {
    void EjectDLL() { FreeLibraryAndExitThread(InjectedIntoModule, 0); }
}
