#pragma once

#include <Logging.h>
#include <ModdingFramework/Runtime/ModManagement.h>
#include <ModdingFramework/Runtime/UI.h>

namespace ModdingFramework::Runtime {

    void Boot() {
        Log("Booting Modding Framework");
        ModManagement::Boot();
        UI::Boot();
    }
}
