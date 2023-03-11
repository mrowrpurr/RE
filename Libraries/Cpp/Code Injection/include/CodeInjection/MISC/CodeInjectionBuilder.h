#pragma once

#include <memory>

#include "CodeInjecting/CodeInjection.h"

namespace CodeInjecting {

    class CodeInjectionBuilder {
        std::shared_ptr<CodeInjection> _injection;
        std::string                    _configuringState = "";

    public:
        CodeInjectionBuilder& On(const std::string& stateName) {
            _configuringState = stateName;
            return *this;
        }

        CodeInjectionBuilder& PerformAction(CodeInjectionAction action) {
            _injection->AddAction(_configuringState, std::move(action));
            return *this;
        }
    };
}
