#pragma once

#include "IMod.h"

namespace ModdingFramework {

    struct IModLoader {
        virtual bool LoadMod(IMod* mod)   = 0;
        virtual bool UnloadMod(IMod* mod) = 0;
    };
}
