#pragma once

#include <memory>

#include "StatefulApp/Variables.h"

namespace StatefulApp {

    class Action {
    public:
        virtual void Perform(std::shared_ptr<Variables> variables) = 0;
    };
}
