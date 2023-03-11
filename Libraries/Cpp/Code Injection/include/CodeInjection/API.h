#pragma once

#include "CodeInjection/Injection.h"
#include "CodeInjection/Registry.h"

namespace CodeInjection {

    Injection& Inject(const std::string& name) { return *Registry::GetSingleton().Register(name); }
}
