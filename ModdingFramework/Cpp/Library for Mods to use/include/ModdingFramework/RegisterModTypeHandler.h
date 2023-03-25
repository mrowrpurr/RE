#pragma once

#include <string>

#include "ModdingFrameworkTypeInstance.h"
#include "Types/Mod.h"

namespace ModdingFramework {

    void RegisterModTypeHandler(
        const std::string& modType, void (*onloadCallback)(Types::Mod*),
        void (*onunloadCallback)(Types::Mod*)
    ) {
        GetModdingFramework()->RegisterModTypeHandler(
            modType.c_str(), onloadCallback, onunloadCallback
        );
    }
}
