#pragma once

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "../Config.h"

namespace Logging::Adapters {

    class SpdlogAdapter {
        ~SpdlogAdapter()                               = default;
        SpdlogAdapter(const SpdlogAdapter&)            = delete;
        SpdlogAdapter(SpdlogAdapter&&)                 = delete;
        SpdlogAdapter& operator=(const SpdlogAdapter&) = delete;
        SpdlogAdapter& operator=(SpdlogAdapter&&)      = delete;

        SpdlogAdapter() {
            if (Config::LogFilePath.empty()) SpdlogLogger = spdlog::stdout_color_mt("console");
            else SpdlogLogger = spdlog::basic_logger_mt("basic_logger", Config::LogFilePath, true);
            SpdlogLogger->set_level(spdlog::level::trace);
            SpdlogLogger->flush_on(spdlog::level::trace);
            SpdlogLogger->set_pattern("%v");
        }

    public:
        std::shared_ptr<spdlog::logger> SpdlogLogger;

        static SpdlogAdapter& GetSingleton() {
            static SpdlogAdapter singleton;
            return singleton;
        }
    };
}

#define OutputLogLine(...) \
    Logging::Adapters::SpdlogAdapter::GetSingleton().SpdlogLogger->info(__VA_ARGS__)
