#pragma once

#include <StatefulApp/Variables.h>

#include "CodeInjection/Injection.h"
#include "CodeInjection/Registry.h"

namespace CodeInjection {

    Injection& Inject(const std::string& name) { return *Registry::GetSingleton().Register(name); }

    typedef StatefulApp::Variables&                     Variables;
    typedef CodeInjection::AllocatedMemoryActionBuilder AllocatedMemory;
}
