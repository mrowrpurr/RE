#pragma once

#include <Serialization.h>

#include <filesystem>

#include "Mod.h"

namespace ModdingFramework::Runtime {

    Mod ModFromINI(const std::filesystem::path& iniPath) {
        auto ini        = Serialization::LoadFile(iniPath);
        auto modSection = ini["Mod"];
        return Mod{
            modSection.Get("name"),   modSection.Get("version"), modSection.Get("type"),
            modSection.Get("source"), iniPath.parent_path(),
        };
    }
}
