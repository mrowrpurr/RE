#pragma once

#include "IFileSearchPaths.h"
#include "IRuntimeConfig.h"

namespace ModdingFramework {

    struct IModdingRuntime {
        virtual IRuntimeConfig*   GetRuntimeConfig()   = 0;
        virtual IFileSearchPaths* GetFileSearchPaths() = 0;
    };
}
