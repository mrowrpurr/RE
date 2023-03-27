#pragma once

namespace ModdingFramework {

    struct IMod {
        virtual const char* GetName() const    = 0;
        virtual const char* GetVersion() const = 0;
        virtual const char* GetFolder() const  = 0;
        virtual const char* GetType() const    = 0;
        virtual const char* GetSource() const  = 0;
        virtual bool        IsLoaded() const   = 0;
        virtual bool        Load()             = 0;
        virtual bool        Unload()           = 0;
    };
}
