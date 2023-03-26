#pragma once

#include <Logging.h>

#include "ModdingRuntime.h"

namespace ModdingFramework::Runtime {
    void Boot() {
        Log("Booting Modding Framework");
        ModdingRuntime::GetRuntime().Boot();
    }
}
