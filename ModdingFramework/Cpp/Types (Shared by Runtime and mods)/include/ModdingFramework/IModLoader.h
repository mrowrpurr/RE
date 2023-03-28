#pragma once

#include "IMod.h"

namespace ModdingFramework {

    struct IModLoader {
        virtual ~IModLoader()             = default;
        virtual bool LoadMod(IMod* mod)   = 0;
        virtual bool UnloadMod(IMod* mod) = 0;
    };
}
