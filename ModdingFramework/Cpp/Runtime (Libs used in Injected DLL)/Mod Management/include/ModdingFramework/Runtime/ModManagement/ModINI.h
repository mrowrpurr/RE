#pragma once

#include <ModdingFramework/Runtime/Core/Mod.h>
#include <Serialization.h>

#include <filesystem>

namespace ModdingFramework::Runtime::ModManagement {

    Core::Mod ModFromINI(const std::filesystem::path& iniPath) {
        auto ini        = Serialization::LoadFile(iniPath);
        auto modSection = ini["Mod"];
        return Core::Mod{
            modSection.Get("name"),   modSection.Get("version"), modSection.Get("type"),
            modSection.Get("source"), iniPath.parent_path(),
        };
    }
}
