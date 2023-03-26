#pragma once

namespace ModdingFramework {

    struct IRuntimeConfig {
        virtual const char* GetGameExecutable() = 0;
        virtual const char* GetModsFolderPath() = 0;
    };
}
