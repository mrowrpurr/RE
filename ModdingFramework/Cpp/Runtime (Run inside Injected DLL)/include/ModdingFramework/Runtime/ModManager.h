#pragma once

namespace ModdingFramework::Runtime {

    class ModManager {
        ModManager(const ModManager&)            = delete;
        ModManager(ModManager&&)                 = delete;
        ModManager& operator=(const ModManager&) = delete;
        ModManager& operator=(ModManager&&)      = delete;

    public:
        ModManager()  = default;
        ~ModManager() = default;
    };
}
