#pragma once

#include <ModdingFramework\IFileSearchPaths.h>

#include <filesystem>
#include <string>
#include <vector>

namespace ModdingFramework::Runtime {

    class FileSearchPaths : public IFileSearchPaths {
        std::vector<std::string> _paths;

        FileSearchPaths(const FileSearchPaths&)            = delete;
        FileSearchPaths(FileSearchPaths&&)                 = delete;
        FileSearchPaths& operator=(const FileSearchPaths&) = delete;
        FileSearchPaths& operator=(FileSearchPaths&&)      = delete;

    public:
        FileSearchPaths()  = default;
        ~FileSearchPaths() = default;

        size_t      GetCount() override { return _paths.size(); }
        const char* Get(size_t i) override { return _paths[i].c_str(); }
        void        Append(const char* path) override { _paths.push_back(path); }
        void        Clear() override { _paths.clear(); }
        const char* Find(const char* path) override {
            for (const auto& p : _paths)
                if (std::filesystem::exists(p + path)) return p.c_str();
            return nullptr;
        }

        const std::vector<std::string>& GetPaths() const { return _paths; }

        static constexpr auto SEARCH_PATHS_ENV_VAR_NAME = "MODDING_FRAMEWORK_SEARCH_PATHS";

        static void LoadFromEnvironmentVariable(
            FileSearchPaths& paths, const char* envVarName = SEARCH_PATHS_ENV_VAR_NAME
        ) {
            const char* envVar = getenv(envVarName);
            if (envVar) {
                std::string envVarStr(envVar);
                size_t      start = 0;
                size_t      end   = envVarStr.find(';');
                while (end != std::string::npos) {
                    paths.Append(envVarStr.substr(start, end - start).c_str());
                    start = end + 1;
                    end   = envVarStr.find(';', start);
                }
                paths.Append(envVarStr.substr(start, end - start).c_str());
            }
        }
    };
}
