#pragma once

#include "IMod.h"
#include "IModLoader.h"

namespace ModdingFramework {

    struct IModLoaders {
        virtual bool         RegisterLoader(const char* type, IModLoader* loader) = 0;
        virtual bool         UnregisterLoader(const char* type)                   = 0;
        virtual bool         IsSupportedType(const char* type)                    = 0;
        virtual IModLoader*  GetLoader(const char* type)                          = 0;
        virtual IModLoader*  GetLoader(size_t index)                              = 0;
        virtual void         UnregisterAll()                                      = 0;
        virtual size_t       GetLoaderCount()                                     = 0;
        virtual const char** GetLoaderTypes()                                     = 0;
        virtual bool         LoadMod(IMod* mod)                                   = 0;
        virtual bool         UnloadMod(IMod* mod)                                 = 0;
    };
}
