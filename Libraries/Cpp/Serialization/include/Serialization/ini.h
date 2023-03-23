#pragma once

#include <StringFormatting.h>

#include <any>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Helpers/UnorderedMapReader.h"
#include "SimpleIni.h"

namespace Serialization {

    Helpers::UnorderedMapReader LoadIniFile(const std::filesystem::path& path) {
        CSimpleIniA ini;

        ini.SetUnicode();
        auto iniLoadError = ini.LoadFile(path.c_str());

        if (iniLoadError < 0)
            throw std::runtime_error(string_format("Failed to load file. File: {}", path.string()));

        std::unordered_map<std::string, std::any> resultMap;

        CSimpleIniA::TNamesDepend sections;
        ini.GetAllSections(sections);

        for (auto& section : sections) {
            std::unordered_map<std::string, std::any> sectionMap;

            CSimpleIniA::TNamesDepend keys;
            ini.GetAllKeys(section.pItem, keys);

            for (auto& key : keys) {
                auto value            = ini.GetValue(section.pItem, key.pItem);
                sectionMap[key.pItem] = std::string(value);
            }

            resultMap[section.pItem] = sectionMap;
        }

        return Helpers::UnorderedMapReader{resultMap};
    }
}
