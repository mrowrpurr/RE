#pragma once

#include <Logging.h>
#include <ModdingFramework/Runtime/System.h>
#include <Serialization.h>

#include <filesystem>

#include "ModDiscovery.h"

namespace ModdingFramework::Runtime::ModManagement {

    void Boot() {
        Log("Booting Mod Management");

        // Do, like, something... I dunno, to get/create a variety
        // of ModDiscoverer instances for different types of mods
        ModDiscovery(System::GetSystem(), {{}}).DiscoverMods();
    }
}
