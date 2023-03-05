#pragma once

#include <string>

#include "Logging/Private/OnLoadFunctionRunner.h"

namespace Logging::Config {

    // The path to the log file.
    std::string LogFilePath = "Log.txt";
}

#define LogFilePath(filePath)                                    \
    Logging::Util::OnLoadFunctionRunner ___loggingLogFileSetup { \
        []() { Logging::LogFilePath = filePath; }                \
    }
