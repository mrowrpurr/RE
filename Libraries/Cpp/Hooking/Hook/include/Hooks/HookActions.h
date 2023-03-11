#pragma once

#include <vector>

#include "Hooks/FunctionTypes.h"
#include "Hooks/HookAction.h"
#include "Hooks/Registers.h"

namespace Hooks {

    class HookActions {
        std::vector<HookAction> _actions;

    public:
        HookActions() = default;

        HookActions& Call(std::function<void(Registers::RegistersReader&)> callable) {
            _actions.push_back(HookAction{callable});
            return *this;
        }

        HookActions& Call(uint32_t address) {
            _actions.push_back(HookAction{HookActionType::CALL, address});
            return *this;
        }

        HookActions& Jmp(uint32_t address) {
            _actions.push_back(HookAction{HookActionType::JMP, address});
            return *this;
        }

        HookActions& CallFunction(FunctionTypes::Void functionPtr) {
            _actions.push_back(HookAction{
                HookActionType::CALL_FN, reinterpret_cast<uint32_t>(functionPtr)});
            return *this;
        }

        HookActions& JmpToFunction(FunctionTypes::Void functionPtr) {
            _actions.push_back(HookAction{
                HookActionType::JMP_FN, reinterpret_cast<uint32_t>(functionPtr)});
            return *this;
        }

        HookActions& SaveRegisters() {
            _actions.push_back(HookAction{HookActionType::SAVE_REGISTERS});
            return *this;
        }

        HookActions& RestoreRegisters() {
            _actions.push_back(HookAction{HookActionType::RESTORE_REGISTERS});
            return *this;
        }

        HookActions& WriteByte(uint8_t byte) {
            _actions.push_back(HookAction{Bytes{{byte}}});
            return *this;
        }

        HookActions& WriteBytes(std::vector<uint8_t> bytes) {
            _actions.push_back(HookAction{Bytes{bytes}});
            return *this;
        }

        HookActions& Ret() { return WriteByte(0xC3); }
        HookActions& Nop() { return WriteByte(0x90); }
        HookActions& Pushad() { return WriteBytes({0x60}); }
        HookActions& Popad() { return WriteBytes({0x61}); }
        HookActions& Pushfd() { return WriteBytes({0x9C}); }
        HookActions& Popfd() { return WriteBytes({0x9D}); }
    };
}