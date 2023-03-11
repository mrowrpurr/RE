#pragma once

#include <StatefulApp/Action.h>

#include <vector>

#include "CodeInjection/Actions/ByteWriterActionBase.h"

namespace CodeInjection {
    class ByteWriterActionGroup : public StatefulApp::Action, public ByteWriterActionBase {
        std::vector<ByteWriterActionBase> _byteWriterActions;

    public:
        size_t GetByteCount() override {
            size_t byteCount = 0;
            for (auto& byteWriterAction : _byteWriterActions)
                byteCount += byteWriterAction.GetByteCount();
            return byteCount;
        }

        void Perform() override {
            for (auto& byteWriterAction : _byteWriterActions) byteWriterAction.Perform();
        }

        void AddAction(ByteWriterActionBase byteWriterAction) {
            _byteWriterActions.push_back(byteWriterAction);
        }
    };
}
