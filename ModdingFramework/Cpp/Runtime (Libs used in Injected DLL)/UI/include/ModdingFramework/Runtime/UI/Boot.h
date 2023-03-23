#pragma once

#include <Logging.h>

#include "App.h"

namespace ModdingFramework::Runtime::UI {
    void Boot() {
        Log("Booting Modding Framework UI");
        App::RunUI();
    }
}
