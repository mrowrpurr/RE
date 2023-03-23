#pragma once

#include <Logging.h>
#include <ModdingFramework/Runtime/Core/Mod.h>
#include <StringFormatting.h>

#include <unordered_map>
#include <utility>

namespace ModdingFramework::Runtime::ModManagement {

    namespace {
        using tupleKeySignature = std::tuple<std::string, std::string>;

        // https://stackoverflow.com/a/72419098
        // CC BY-SA 4.0
        struct hash_tuple {
            size_t operator()(const tupleKeySignature& x) const {
                std::hash<std::string> h{};
                return h(std::get<0>(x)) ^ h(std::get<1>(x));
            }
        };
    }

    class ModRegistry {
        std::unordered_map<std::tuple<std::string, std::string>, Core::Mod, hash_tuple> _mods;

    public:
        void RegisterMod(Core::Mod mod) {
            if (_mods.contains(std::make_pair(mod.GetName(), mod.GetVersion()))) {
                throw std::runtime_error(string_format(
                    "Mod with name '{}' and version '{}' already exists", mod.GetName(),
                    mod.GetVersion()
                ));
            }
            Log("Registered mod '{}'", mod.GetName());
            _mods.emplace(std::make_pair(mod.GetName(), mod.GetVersion()), std::move(mod));
        }
    };
}
