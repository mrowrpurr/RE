#pragma once

#include "Mod.h"

namespace ModdingFramework::Types {

    class ModdingFrameworkRuntime {
    public:
        // TODO - more like Runtime::GetModTypeHandler().Register() and shit
        virtual void RegisterModTypeHandler(
            const char* modType, void (*onloadCallback)(Mod*), void (*onunloadCallback)(Mod*)
        );
    };
}
