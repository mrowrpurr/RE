#pragma once

#include <vector>

#include "ModDiscoverer.h"
#include "System.h"

namespace ModdingFramework::Runtime {

    class ModDiscovery {
        System&                    _system;
        std::vector<ModDiscoverer> _discoverers;

    public:
        ModDiscovery(System& system, std::vector<ModDiscoverer> discoverers)
            : _system(system), _discoverers(discoverers) {}

        void DiscoverMods() {
            for (auto& discoverer : _discoverers) discoverer.DiscoverMods(_system);
        }
    };
}
