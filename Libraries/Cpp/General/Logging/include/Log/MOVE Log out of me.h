#pragma once

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

namespace Logging {
    std::string LogFilePath;

    class Logger {
        Logger() : _log(spdlog::basic_logger_mt("basic_logger", LogFilePath, true)) {
            _log->set_level(spdlog::level::trace);
            _log->flush_on(spdlog::level::trace);
            _log->set_pattern("%v");
        }

        ~Logger()                        = default;
        Logger(const Logger&)            = delete;
        Logger(Logger&&)                 = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&)      = delete;

    public:
        std::shared_ptr<spdlog::logger> _log;

        static Logger& GetGlobalInstance() {
            static Logger singleton;
            return singleton;
        }
    };

    namespace Util {
        class OnLoadFunctionRunner {
            std::function<void()> _function;

        public:
            OnLoadFunctionRunner(std::function<void()> function) : _function(function) { _function(); }
        };
    }
}

#define LogFile(filePath)                                        \
    Logging::Util::OnLoadFunctionRunner ___loggingLogFileSetup { \
        []() { Logging::LogFilePath = filePath; }                \
    }

#define Log(...) Logging::Logger::GetGlobalInstance()._log->info(__VA_ARGS__)
