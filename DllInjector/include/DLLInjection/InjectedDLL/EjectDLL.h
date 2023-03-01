#pragma once

#include "DLLInjection/InjectedDLL/Module.h"

namespace DLLInjection {
    void EjectDLL() { FreeLibraryAndExitThread(DLLInjection::InjectedIntoModule, 0); }
}