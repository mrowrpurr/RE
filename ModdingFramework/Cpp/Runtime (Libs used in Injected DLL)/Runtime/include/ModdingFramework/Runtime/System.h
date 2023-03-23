#pragma once

#include <ModdingFramework/Runtime/ModManagement/ModRegistry.h>

namespace ModdingFramework::Runtime {

    class System {
        ModManagement::ModRegistry _registry;

    public:
        static System& GetSystem() {
            static System instance;
            return instance;
        }

        ModManagement::ModRegistry& GetModRegistry() { return _registry; }
    };
}
