#pragma once

#include <Logging.h>

#include <functional>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "Actions.h"
#include "InjectionAction.h"
#include "InjectionVariables.h"

namespace CodeInjection {

    class InjectionBuilder {
        std::shared_ptr<std::vector<std::shared_ptr<InjectionAction>>> _actions;
        std::shared_ptr<InjectionVariables>                            _variables;

    public:
        InjectionBuilder(std::shared_ptr<InjectionVariables> variables) : _variables(variables) {}

        void SetActionsContainer(std::shared_ptr<std::vector<std::shared_ptr<InjectionAction>>> actions) {
            _actions = actions;
        }

        template <typename T>
        InjectionBuilder& AddAction(T action) {
            _actions->push_back(std::make_shared<T>(action));
            return *this;
        }

        InjectionBuilder& ReadBytes(Actions::ReadBytesActionParams actionParams) {
            AddAction(Actions::ReadBytesAction(actionParams));
            return *this;
        }

        InjectionBuilder& ReadBytes(
            const std::string& addressVariable, const std::string& outVariable, size_t byteCount
        ) {
            AddAction(Actions::ReadBytesAction({
                .addressVariable = addressVariable,
                .outVariable     = outVariable,
                .byteCount       = byteCount,
            }));
            return *this;
        }

        InjectionBuilder& WriteBytes(Actions::WriteBytesActionParams actionParams) {
            AddAction(Actions::WriteBytesAction(actionParams));
            return *this;
        }

        InjectionBuilder& WriteBytes(const std::string& bytesVariable) {
            AddAction(Actions::WriteBytesAction({.bytesVariable = bytesVariable}));
            return *this;
        }

        InjectionBuilder& WriteBytes(const std::string& addressVariable, const std::string& bytesVariable) {
            AddAction(Actions::WriteBytesAction({.addressVariable = addressVariable, .bytesVariable = bytesVariable}));
            return *this;
        }

        InjectionBuilder& WriteJmp(Actions::WriteJmpActionParams actionParams) {
            AddAction(Actions::WriteJmpAction(actionParams));
            return *this;
        }

        InjectionBuilder& WriteJmp(const std::string& toAddressVariable) {
            AddAction(Actions::WriteJmpAction({.toAddressVariable = toAddressVariable}));
            return *this;
        }

        InjectionBuilder& WriteJmp(const std::string& fromAddressVariable, const std::string& toAddressVariable) {
            AddAction(Actions::WriteJmpAction(
                {.fromAddressVariable = fromAddressVariable, .toAddressVariable = toAddressVariable}
            ));
            return *this;
        }

        InjectionBuilder& WriteCall(Actions::WriteCallActionParams actionParams) {
            AddAction(Actions::WriteCallAction(actionParams));
            return *this;
        }

        InjectionBuilder& WriteNop(Actions::WriteNopActionParams actionParams) {
            AddAction(Actions::WriteNopAction(actionParams));
            return *this;
        }

        InjectionBuilder& WriteAssembly(Actions::WriteAssemblyActionParams actionParams) {
            AddAction(Actions::WriteAssemblyAction(actionParams));
            return *this;
        }

        InjectionBuilder& WriteAssembly(std::function<void(Xbyak::CodeGenerator&)> code) {
            AddAction(Actions::WriteAssemblyAction({.code = code}));
            return *this;
        }

        InjectionBuilder& AllocateMemory(Actions::AllocateMemoryActionParams actionParams) {
            AddAction(Actions::AllocateMemoryAction(actionParams));
            return *this;
        }

        InjectionBuilder& AllocateMemory(
            const std::string& addressVariable, std::function<void(InjectionBuilder&)> code
        ) {
            AddAction(Actions::AllocateMemoryAction({.addressVariable = addressVariable, .code = code}));
            return *this;
        }

        InjectionBuilder& DeallocateMemory(Actions::DeallocateMemoryActionParams actionParams) {
            AddAction(Actions::DeallocateMemoryAction(actionParams));
            return *this;
        }

        InjectionBuilder& DeallocateMemory(const std::string& addressVariable) {
            AddAction(Actions::DeallocateMemoryAction({.addressVariable = addressVariable}));
            return *this;
        }

        InjectionBuilder& Call(Actions::CallActionParams actionParams) {
            AddAction(Actions::CallAction(actionParams));
            return *this;
        }

        InjectionBuilder& Call(std::function<void(Registers::RegistersReader&)> code) {
            AddAction(Actions::CallAction({.function = code}));
            return *this;
        }

        InjectionBuilder& SaveRegisters(Actions::SaveRegistersActionParams actionParams) {
            AddAction(Actions::SaveRegistersAction(actionParams));
            return *this;
        }

        InjectionBuilder& SaveRegisters(std::unordered_set<Register> registers) {
            AddAction(Actions::SaveRegistersAction({.registers = registers}));
            return *this;
        }

        InjectionBuilder& SaveGeneralPurposeRegisters() {
            AddAction(Actions::SaveRegistersAction({.registers = Registers::GetGeneralPurposeRegisters()}));
            return *this;
        }

        InjectionBuilder& RestoreRegisters(Actions::RestoreRegistersActionParams actionParams) {
            AddAction(Actions::RestoreRegistersAction(actionParams));
            return *this;
        }

        InjectionBuilder& RestoreRegisters(std::unordered_set<Register> registers) {
            AddAction(Actions::RestoreRegistersAction({.registers = registers}));
            return *this;
        }

        InjectionBuilder& RestoreGeneralPurposeRegisters() {
            AddAction(Actions::RestoreRegistersAction({.registers = Registers::GetGeneralPurposeRegisters()}));
            return *this;
        }

        InjectionBuilder& FindBytes(Actions::FindBytesActionParams actionParams) {
            AddAction(Actions::FindBytesAction(actionParams));
            return *this;
        }

        InjectionBuilder& FindBytes(
            const std::string& module, const std::string& bytesString, const std::string& outVariable,
            size_t startOffset = 0x0
        ) {
            AddAction(Actions::FindBytesAction({
                .module      = module,
                .bytesString = bytesString,
                .outVariable = outVariable,
                .startOffset = startOffset,
            }));
            return *this;
        }

        template <typename T>
        InjectionBuilder& Var(const std::string& name, T value) {
            Log("Set Variable: {} ({})", name, typeid(T).name());
            _variables->Set(name, value);
            return *this;
        }

        template <typename T>
        T& Var(const std::string& name) {
            Log("Get Variable: {} ({})", name, typeid(T).name());
            return _variables->Get<T>(name);
        }
    };
}