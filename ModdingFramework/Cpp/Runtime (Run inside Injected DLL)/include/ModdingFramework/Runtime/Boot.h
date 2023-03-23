#pragma once

#include <Logging.h>

#include "ModDiscovery.h"
#include "System.h"
#include "UI.h"


namespace ModdingFramework::Runtime {

    void Boot() {
        Log("Booting Modding Framework");
        ModDiscovery(System::GetSystem(), {{}}).DiscoverMods();
        UI::Run();
    }
}
