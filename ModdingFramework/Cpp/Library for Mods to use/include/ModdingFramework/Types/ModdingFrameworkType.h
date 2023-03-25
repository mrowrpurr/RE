#pragma once

#include "Mod.h"

namespace ModdingFramework::Types {

    class ModdingFrameworkType {
    public:
        virtual void RegisterModTypeHandler(
            const char* modType, void (*onloadCallback)(Mod*), void (*onunloadCallback)(Mod*)
        );
    };
}
