#pragma once

#include <Logging.h>
#include <ModdingFramework/Types/ModdingFrameworkType.h>

#include <string>

namespace ModdingFramework::Runtime {

    class ModdingFrameworkTypeImpl : public Types::ModdingFrameworkType {
        ModdingFrameworkTypeImpl()                                           = default;
        ~ModdingFrameworkTypeImpl()                                          = default;
        ModdingFrameworkTypeImpl(const ModdingFrameworkTypeImpl&)            = delete;
        ModdingFrameworkTypeImpl(ModdingFrameworkTypeImpl&&)                 = delete;
        ModdingFrameworkTypeImpl& operator=(const ModdingFrameworkTypeImpl&) = delete;
        ModdingFrameworkTypeImpl& operator=(ModdingFrameworkTypeImpl&&)      = delete;
        Types::Mod someRandomMod = Types::Mod{"Some random Mod!", "1.2.3", "python", "..."};

    public:
        static ModdingFrameworkTypeImpl& GetSingleton() {
            static ModdingFrameworkTypeImpl singleton;
            return singleton;
        }

        void RegisterModTypeHandler(
            const char* modType, void (*onloadCallback)(Types::Mod*),
            void (*onunloadCallback)(Types::Mod*)
        ) override {
            Log("!!!! Registering mod type handler: {}", modType);
            if (onloadCallback != nullptr) {
                onloadCallback(&someRandomMod);
            } else {
                Log("!!!! onloadCallback is nullptr");
            }
            if (onunloadCallback != nullptr) {
                onunloadCallback(&someRandomMod);
            } else {
                Log("!!!! onunloadCallback is nullptr");
            }
        };
    };
}
