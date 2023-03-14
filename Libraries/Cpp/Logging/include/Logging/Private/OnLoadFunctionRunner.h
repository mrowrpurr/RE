#pragma once

#include <functional>

namespace Logging::Private {

    // This class is used to run a function when the library is loaded.
    // Used by macros Log and LogFilePath.
    class OnLoadFunctionRunner {
        std::function<void()> _function;

    public:
        OnLoadFunctionRunner(std::function<void()> function) : _function(function) { _function(); }
    };
}
