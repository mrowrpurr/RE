#pragma once

#include <StatefulApp/Action.h>
#include <StatefulApp/Variables.h>

#include <memory>
#include <vector>

#include "CodeInjection/Actions/ByteWriterActionBase.h"

namespace CodeInjection {
    class ByteWriterActionGroup : public ByteWriterActionBase {
        std::vector<std::shared_ptr<ByteWriterActionBase>> _byteWriterActions;

    public:
        size_t GetByteCount() override {
            size_t byteCount = 0;
            for (auto& byteWriterAction : _byteWriterActions)
                byteCount += byteWriterAction->GetByteCount();
            return byteCount;
        }

        void Perform(std::shared_ptr<StatefulApp::Variables> variables) override {
            for (auto& byteWriterAction : _byteWriterActions) byteWriterAction->Perform(variables);
        }

        template <typename T>
        void AddAction(T action) {
            _byteWriterActions.push_back(std::make_shared<T>(action));
        }
    };
}
