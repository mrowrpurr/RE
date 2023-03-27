#pragma once

#include <Logging.h>

#include "ModdingRuntime.h"
#include "ModdingUI.h"

namespace ModdingFramework::Runtime {
    void Boot() {
        Log("Booting Modding Framework");
        ModdingRuntime::GetRuntime().Boot();
        ModdingUI::Run();
    }
}
