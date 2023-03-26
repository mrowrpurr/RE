#pragma once

namespace ModdingFramework::Runtime {

    class ModdingRuntime {
        ModdingRuntime()                                 = default;
        ~ModdingRuntime()                                = default;
        ModdingRuntime(const ModdingRuntime&)            = delete;
        ModdingRuntime(ModdingRuntime&&)                 = delete;
        ModdingRuntime& operator=(const ModdingRuntime&) = delete;
        ModdingRuntime& operator=(ModdingRuntime&&)      = delete;

    public:
        static ModdingRuntime& GetRuntime() {
            static ModdingRuntime runtime;
            return runtime;
        }

        void ReloadConfig() {}
    };
}
