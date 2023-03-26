#pragma once

#include <Logging.h>

#include "ModdingRuntime.h"
#include "UI.h"

namespace ModdingFramework::Runtime {
    void Boot() {
        Log("Booting Modding Framework");
        ModdingRuntime::GetRuntime().Boot();

        // For now, load the UI automatically
        UI::Run();
    }
}
