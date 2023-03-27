#pragma once

#include "IMod.h"

namespace ModdingFramework {

    struct IModRegistry {
        virtual void   RegisterMod(IMod* mod)                              = 0;
        virtual void   UnregisterMod(IMod* mod)                            = 0;
        virtual void   UnregisterAllMods()                                 = 0;
        virtual size_t GetModCount() const                                 = 0;
        virtual IMod*  GetMod(size_t index) const                          = 0;
        virtual IMod*  GetMod(const char* name) const                      = 0;
        virtual IMod*  GetMod(const char* name, const char* version) const = 0;
    };
}
