#pragma once

#include <string>

#include "Logging/Private/OnLoadFunctionRunner.h"

namespace Logging::Config {

    // The path to the log file.
    std::string LogFilePath = "";
}

#define SetLogFilePath(filePath)                                    \
    Logging::Private::OnLoadFunctionRunner ___loggingLogFileSetup { \
        []() { Logging::Config::LogFilePath = filePath; }           \
    }
