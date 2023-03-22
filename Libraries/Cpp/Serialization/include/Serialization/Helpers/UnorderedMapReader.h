#pragma once

#include <any>
#include <string>
#include <unordered_map>

namespace Serialization::Helpers {

    class UnorderedMapReader {
        const std::unordered_map<std::string, std::any> _map;  // Copy!

    public:
        UnorderedMapReader(const std::unordered_map<std::string, std::any>& map) : _map(map) {}

        template <typename T>
        T Get(const std::string& key) const {
            return std::any_cast<T>(_map.at(key));
        }

        template <typename T>
        T Get(const std::string& key, const T& defaultValue) const {
            if (_map.contains(key)) return Get<T>(key);
            return defaultValue;
        }

        std::string Get(const std::string& key) const { return Get<std::string>(key); }

        UnorderedMapReader GetMap(const std::string& key) const {
            return UnorderedMapReader(Get<std::unordered_map<std::string, std::any>>(key));
        }

        std::string GetString(const std::string& key) const { return Get<std::string>(key); }

        std::string GetString(const std::string& key, const std::string& defaultValue) const {
            return Get<std::string>(key, defaultValue);
        }

        UnorderedMapReader operator[](const std::string& key) const { return GetMap(key); }
    };
}
