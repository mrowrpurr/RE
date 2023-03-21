#pragma once

#include <any>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "ini.h"
#include "yaml.h"

namespace Serialization {

    std::unordered_map<std::string, std::any> LoadFile(const std::string& path) {
        if (path.ends_with(".ini")) return LoadIniFile(path);
        throw std::runtime_error(string_format("Unsupported file type. File: {}", path));
    }
}
