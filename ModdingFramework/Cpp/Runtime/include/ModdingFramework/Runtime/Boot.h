#pragma once

#include <Logging.h>
#include <ModdingFramework/PluginManager.h>
#include <ModdingFramework/UI.h>

namespace ModdingFramework::Runtime {

    void Boot() {
        Log("Booting Modding Framework");
        PluginManager::Boot();
        UI::Boot();
    }
}
