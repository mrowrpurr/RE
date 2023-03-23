#pragma once

#include <any>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Helpers/UnorderedMapReader.h"
#include "ini.h"
#include "yaml.h"

namespace Serialization {

    Helpers::UnorderedMapReader LoadFile(const std::filesystem::path path) {
        if (path.string().ends_with(".ini")) return LoadIniFile(path);
        throw std::runtime_error(string_format("Unsupported file type. File: {}", path.string()));
    }
}
