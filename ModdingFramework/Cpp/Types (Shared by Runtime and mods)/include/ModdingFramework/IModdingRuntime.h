#pragma once

#include "IFileSearchPaths.h"

namespace ModdingFramework {

    struct IModdingRuntime {
        virtual IFileSearchPaths* GetFileSearchPaths() = 0;
    };
}
