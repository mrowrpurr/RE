#pragma once

namespace ModdingFramework {

    struct IFileSearchPaths {
        virtual const char* GetPath()                 = 0;
        virtual void        SetPath(const char* path) = 0;
    };
}
