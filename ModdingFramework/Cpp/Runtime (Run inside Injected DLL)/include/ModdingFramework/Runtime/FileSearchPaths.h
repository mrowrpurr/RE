#pragma once

#include <ModdingFramework\IFileSearchPaths.h>

#include <filesystem>
#include <string>
#include <vector>

namespace ModdingFramework::Runtime {

    class FileSearchPaths {
    public:
        class CInterface : public IFileSearchPaths {
            FileSearchPaths& _paths;

        public:
            CInterface(FileSearchPaths& paths) : _paths(paths) {}

            size_t      GetCount() override { return _paths.GetPaths().size(); }
            const char* Get(size_t i) override { return _paths.GetPaths().at(i).c_str(); }
            void        Append(const char* path) override { _paths.Append(path); }
            void        Clear() override { _paths.Clear(); }
        };

    private:
        CInterface _cInterface{*this};

        std::vector<std::string> _paths;

        FileSearchPaths(const FileSearchPaths&)            = delete;
        FileSearchPaths(FileSearchPaths&&)                 = delete;
        FileSearchPaths& operator=(const FileSearchPaths&) = delete;
        FileSearchPaths& operator=(FileSearchPaths&&)      = delete;

    public:
        FileSearchPaths()  = default;
        ~FileSearchPaths() = default;

        std::string Find(const std::string& fileName) {
            for (auto& path : _paths) {
                auto fullPath = std::filesystem::path{path} / fileName;
                if (std::filesystem::exists(fullPath)) return fullPath.string();
            }
            return "";
        }

        const std::vector<std::string>& GetPaths() const { return _paths; }
        void                            Append(const std::string& path) { _paths.push_back(path); }
        void                            Clear() { _paths.clear(); }

        static constexpr auto SEARCH_PATHS_ENV_VAR_NAME = "MODDING_FRAMEWORK_SEARCH_PATHS";
        static constexpr auto SEARCH_PATHS_DEFAULT      = ";Data;Data Files";

        static void LoadFromEnvironmentVariable(
            FileSearchPaths& paths, const char* envVarName = SEARCH_PATHS_ENV_VAR_NAME,
            const char* defaultPaths = SEARCH_PATHS_DEFAULT
        ) {
            const char* searchPaths = std::getenv(envVarName);
            if (!searchPaths) searchPaths = defaultPaths;
            auto   envVarStr = std::string{searchPaths};
            size_t start     = 0;
            size_t end       = envVarStr.find(';');
            while (end != std::string::npos) {
                paths.Append(envVarStr.substr(start, end - start).c_str());
                start = end + 1;
                end   = envVarStr.find(';', start);
            }
            paths.Append(envVarStr.substr(start, end - start).c_str());
        }

        static void Load(FileSearchPaths& paths) { LoadFromEnvironmentVariable(paths); }
        static void Reload(FileSearchPaths& paths) {
            paths.Clear();
            Load(paths);
        }

        IFileSearchPaths* GetCInterface() { return &_cInterface; }
    };
}
