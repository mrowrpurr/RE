#pragma once

#include <Logging.h>
#include <ModdingFramework/Runtime/ModManager.h>
#include <ModdingFramework/Runtime/UI.h>

namespace ModdingFramework::Runtime {

    void Boot() {
        Log("Booting Modding Framework");
        ModManager::Boot();
        UI::Boot();
    }
}
