#pragma once

#include <Logging.h>
#include <ModdingFramework/Runtime/System.h>

namespace ModdingFramework::Runtime::ModManagement {

    // TODO - make this abstract and have multiple implementations
    class ModDiscoverer {
    public:
        void DiscoverMods(System&) {
            // TODO - implement
            Log("ModDiscoverer instance is fiscovering mods");
        }
    };
}
