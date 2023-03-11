#pragma once

#include <StatefulApp/Action.h>

namespace CodeInjection {
    class ByteWriterActionBase : public StatefulApp::Action {
    public:
        virtual size_t GetByteCount() = 0;
    };
}
