#pragma once

#include "IFileSearchPaths.h"
#include "IModLoaders.h"
#include "IModRegistry.h"
#include "IRuntimeConfig.h"

namespace ModdingFramework {

    struct IModdingRuntime {
        virtual IFileSearchPaths* GetFileSearchPaths() = 0;
        virtual IRuntimeConfig*   GetRuntimeConfig()   = 0;
        virtual IModRegistry*     GetRegistry()        = 0;
        virtual IModLoaders*      GetModLoaders()      = 0;
    };
}
