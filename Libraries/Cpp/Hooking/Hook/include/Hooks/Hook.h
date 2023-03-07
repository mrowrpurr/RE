#pragma once

#include <functional>
#include <optional>
#include <stdexcept>
#include <string>

#include "Hooks/ArrayOfBytes.h"
#include "Hooks/Bytes.h"
#include "Hooks/FunctionTypes.h"
#include "Hooks/HookAction.h"
#include "Hooks/MemoryBytes.h"
#include "Hooks/Registers.h"

namespace Hooks {

    // Represents a hook to a specific address implemented via a JMP
    class Hook {
        std::string                          _name;
        bool                                 _installed = false;
        std::optional<std::function<void()>> _installFunction;
        std::optional<std::function<void()>> _uninstallFunction;

        Bytes _replacedBytes;

        MemoryBytes _detour;
        uint32_t    _detourByteCount      = 5;  // JMP is 5 bytes
        uint32_t    _detourJumpBackOffset = 0;
        Bytes       _originalDetourBytes;

        MemoryBytes _trampoline;

        std::vector<HookAction> _hookActions;

        void WriteTrampoline() {
            auto requiredSize = 0;
            for (auto& hookAction : _hookActions) {
                Log("[{}] Trampoline Action {} requires {} bytes", _name, hookAction.GetTypeName(),
                    hookAction.CalculateByteCount());
                requiredSize += hookAction.CalculateByteCount();
            }
            Log("[{}] Trampoline Total required size: {}", _name, requiredSize);

            _trampoline.Allocate(requiredSize);
            Log("[{}] Trampoline Allocate {} --> {:x}", _name, requiredSize,
                _trampoline.GetAddress());

            for (auto& hookAction : _hookActions) {
                Log("[{}] Trampoline Writing action: {}", _name, hookAction.GetTypeName());
                hookAction.Write(_trampoline);
                Log("[{}] Trampoline Wrote action: {}", _name, hookAction.GetTypeName());
            }
        }

        Bytes GetDetourBytes() { return _detour.GetBytes(_detourByteCount); }

        void BackupOriginalDetourBytes() { _originalDetourBytes = GetDetourBytes(); }

        void WriteDetour() {
            Log("[{}] Writing detour to {:x}", _name, _detour.GetAddress());
            _detour.WriteProtectedJmp(_trampoline.GetAddress());
            if (_detourByteCount > 5)
                for (uint32_t i = 5; i < _detourByteCount; i++) _detour.WriteProtectedByte(0x90);
            Log("[{}] Wrote detour to {:x}", _name, _detour.GetAddress());
        }

        void RestoreDetourToOriginalBytes() {
            Log("[{}] Restoring detour at {:x} to original bytes", _name, _detour.GetAddress());
            _detour.ClearBytes();
            _detour.WriteProtectedBytes(_originalDetourBytes);
            Log("[{}] Restored detour at {:x} to original bytes", _name, _detour.GetAddress());
        }

        void FreeTrampolineBytes() { _trampoline.Free(); }

    public:
        explicit Hook(const std::string& name) : _name(name) {}

        const std::string& GetName() const { return _name; }
        Hook&              SetName(const std::string& name) {
            _name = name;
            return *this;
        }

        /** Installation / Uninstallation */

        bool IsInstalled() const { return _installed; }

        // Set the function to be called when the hook is installed
        Hook& OnInstall(const std::function<void()>& installFunction) {
            _installFunction = installFunction;
            return *this;
        }

        // Set the function to be called when the hook is uninstalled
        Hook& OnUninstall(const std::function<void()>& uninstallFunction) {
            _uninstallFunction = uninstallFunction;
            return *this;
        }

        void Install() {
            if (_installed) return;
            if (_installFunction.has_value()) {
                _installFunction.value()();
                return;
            }
            if (_detour.GetAddress() == 0) throw std::runtime_error("Hook address not set");
            BackupOriginalDetourBytes();
            WriteTrampoline();
            WriteDetour();
        }

        void Uninstall() {
            if (!_installed) return;
            if (_uninstallFunction.has_value()) {
                _uninstallFunction.value()();
                return;
            }
            if (_detour.GetAddress() == 0)
                throw std::runtime_error("Uninstall called but detour not set");
            RestoreDetourToOriginalBytes();
            FreeTrampolineBytes();
            _detour.ClearBytes();
            _trampoline.Clear();
        }

        bool Toggle() {
            if (_installed)
                Uninstall();
            else
                Install();
            _installed = !_installed;
            return _installed;
        }

        /** Detour Configuration */

        uint32_t GetAddress() const { return _detour.GetAddress(); }
        Hook&    SetAddress(uint32_t address) {
            _detour.SetAddress(address);
            return *this;
        }

        uint32_t GetByteCount() const { return _detourByteCount; }
        Hook&    SetByteCount(uint32_t detourByteCount) {
            _detourByteCount = detourByteCount;
            return *this;
        }

        uint32_t GetJumpBackOffset() const { return _detourJumpBackOffset; }
        Hook&    SetJumpBackOffset(uint32_t detourJumpBackOffset) {
            _detourJumpBackOffset = detourJumpBackOffset;
            return *this;
        }

        Hook& SetArrayOfBytes(
            const std::string& encodedBytes, const std::string& mask = "",
            const std::string& moduleName = "", uint32_t offset = 0
        ) {
            auto address = ArrayOfBytes::Find(encodedBytes, mask, offset, moduleName);
            if (address == 0) throw std::runtime_error("Could not find bytes");
            SetAddress(address);
            return *this;
        }

        /** Hook Actions */

        Hook& Call(std::function<void(Registers::RegistersReader&)> callable) {
            _hookActions.push_back(HookAction{callable});
            return *this;
        }

        Hook& Call(uint32_t address) {
            _hookActions.push_back(HookAction{HookActionType::CALL, address});
            return *this;
        }

        Hook& Jmp(uint32_t address) {
            _hookActions.push_back(HookAction{HookActionType::JMP, address});
            return *this;
        }

        Hook& CallFunction(FunctionTypes::Void functionPtr) {
            _hookActions.push_back(HookAction{
                HookActionType::CALL_FN, reinterpret_cast<uint32_t>(functionPtr)});
            return *this;
        }

        Hook& JmpToFunction(FunctionTypes::Void functionPtr) {
            _hookActions.push_back(HookAction{
                HookActionType::JMP_FN, reinterpret_cast<uint32_t>(functionPtr)});
            return *this;
        }

        Hook& CallOriginalBytes() {
            _hookActions.push_back(HookAction{GetDetourBytes()});
            return *this;
        }

        Hook& SaveRegisters() {
            _hookActions.push_back(HookAction{HookActionType::SAVE_REGISTERS});
            return *this;
        }

        Hook& RestoreRegisters() {
            _hookActions.push_back(HookAction{HookActionType::RESTORE_REGISTERS});
            return *this;
        }

        Hook& JumpBack() {
            _hookActions.push_back(HookAction{
                HookActionType::JMP,
                _detour.GetAddress() + _detourByteCount + _detourJumpBackOffset});
            return *this;
        }

        Hook& WriteByte(uint8_t byte) {
            _hookActions.push_back(HookAction{Bytes{{byte}}});
            return *this;
        }

        Hook& WriteBytes(std::vector<uint8_t> bytes) {
            _hookActions.push_back(HookAction{Bytes{bytes}});
            return *this;
        }

        Hook& Ret() { return WriteByte(0xC3); }
        Hook& Nop() { return WriteByte(0x90); }
        Hook& Pushad() { return WriteBytes({0x60}); }
        Hook& Popad() { return WriteBytes({0x61}); }
        Hook& Pushfd() { return WriteBytes({0x9C}); }
        Hook& Popfd() { return WriteBytes({0x9D}); }
    };
}
