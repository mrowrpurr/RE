#pragma once

#include "Types/ModdingFrameworkType.h"

namespace ModdingFramework {
    namespace {
        Types::ModdingFrameworkType* __modding_framework_instance__;
    }
    Types::ModdingFrameworkType* GetModdingFramework() { return __modding_framework_instance__; }
    void SetModdingFrameworkPtr(Types::ModdingFrameworkType* moddingFrameworkInstance) {
        __modding_framework_instance__ = moddingFrameworkInstance;
    }
}
