#pragma once

namespace ModdingFramework {

    struct IFileSearchPaths {
        virtual size_t      GetCount()               = 0;
        virtual const char* Get(size_t i)            = 0;
        virtual void        Append(const char* path) = 0;
        virtual void        Clear()                  = 0;
        virtual const char* Find(const char* path)   = 0;
    };
}
