#pragma once

#include "CodeInjecting/CodeInjection.h"
#include "CodeInjecting/CodeInjectionBuilder.h"
#include "CodeInjecting/Registry.h"

namespace CodeInjecting::API {

    typedef CodeInjection CodeInjection;

    CodeInjectionBuilder CreateCodeInjection(const std::string& name) {
        auto injection = std::make_shared<CodeInjection>(name);
        Registry::GetRegistry().Register(name, injection);
        return CodeInjectionBuilder(injection);
    }
}
