#pragma once

#include <functional>
#include <optional>
#include <stdexcept>
#include <string>

#include "Hooks/Bytes.h"
#include "Hooks/FunctionTypes.h"
#include "Hooks/HookAction.h"
#include "Hooks/Memory.h"
#include "Hooks/MemoryBytes.h"

namespace Hooks {

    // Represents a hook to a specific address implemented via a JMP
    class Hook {
        std::string                          _name;
        bool                                 _installed = false;
        std::optional<std::function<void()>> _installFunction;
        std::optional<std::function<void()>> _uninstallFunction;

        MemoryBytes _detour;
        uint32_t    _detourByteCount = 5;
        MemoryBytes _trampoline;
        Bytes       _replacedBytes;

        std::vector<HookAction> _hookActions;

        // ...

        uint32_t _detourAddressReplaceBytesCount = 5;
        Bytes    _detourAddressOriginalReplacedBytes;
        uint32_t _jumpOffset = 5;

        // THIS STUFF WILL GO AWAY
        MemoryBytes _targetAddressBytes;
        uint32_t    _newMemoryAddress;
        // std::vector<FunctionTypes::Void> _functionPtrsToCall;
        // std::vector<FuncionType> _functionPtrsToJmpTo;
        bool _trampoline_storeRegistersAtStart          = false;
        bool _trampoline_jumpBackToOriginalAddressAtEnd = true;
        bool _trampoline_writeOriginalBytesAtStart      = false;

        void WriteTrampoline() {
            auto requiredSize = 0;
            for (auto& hookAction : _hookActions) {
                Log("Action byte count: {}", hookAction.CalculateByteCount());
                requiredSize += hookAction.CalculateByteCount();
            }
            Log("Total required size: {}", requiredSize);

            // if (_trampoline_writeOriginalBytesAtStart)
            //     _trampoline.WriteProtectedBytes(ReadOriginalBytes());
            // for (auto functionPtrToCall : _functionPtrsToCall)
            //     _trampoline.WriteProtectedCall((uint32_t)((BYTE*)functionPtrToCall));
            // for (auto functionPtrToJmpTo : _functionPtrsCalculateToJmpTo)
            //     _trampoline.WriteProtectedJmp((uint32_t)((BYTE*)functionPtrToJmpTo));
            // if (_trampoline_jumpBackToOriginalAddressAtEnd)
            //     _trampoline.WriteProtectedJmp(GetJumpBackAddress());
        }

        Bytes& GetDetourBytes() { return _detour.ReadBytes(_detourByteCount); }

        void WriteDetour() {
            // TODO !!!! WRITE NOPs FOR EXTRA BYTES !!!!
            _targetAddressBytes.SetAddress(_detour.GetAddress());
            _targetAddressBytes.WriteProtectedJmp(_trampoline.GetAddress());
        }

    public:
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
            WriteTrampoline();
            WriteDetour();
        }

        void Uninstall() {
            if (!_installed) return;
            if (_uninstallFunction.has_value()) {
                _uninstallFunction.value()();
                return;
            }
            // Else ...
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

        /** Hook Actions */

        Hook& CallFunction(FunctionTypes::Void functionPtr) {
            _hookActions.push_back(HookAction{HookActionType::CALL, functionPtr});
            return *this;
        }

        Hook& CallOriginalBytes() {
            _hookActions.push_back(HookAction{HookActionType::BYTES, GetDetourBytes()});
            return *this;
        }

        //////////////////////////////
        // CLEANUP

        uint32_t GetAddressReplaceBytesCount() const { return _detourAddressReplaceBytesCount; }
        Hook&    SetAddressReplaceBytesCount(uint32_t addressReplaceBytesCount) {
            _detourAddressReplaceBytesCount = addressReplaceBytesCount;
            return *this;
        }
        Bytes& GetAddressOriginalReplacedBytes() { return _detourAddressOriginalReplacedBytes; }
        Hook&  SetAddressOriginalReplacedBytes(std::vector<uint8_t> addressOriginalReplacedBytes) {
            _detourAddressOriginalReplacedBytes = Bytes{addressOriginalReplacedBytes};
            return *this;
        }
        MemoryBytes GetTargetAddressBytes() { return _targetAddressBytes; }
        Hook&       SetTargetAddressBytes(const MemoryBytes& targetAddressBytes) {
            _targetAddressBytes = targetAddressBytes;
            return *this;
        }
        uint32_t GetJumpOffset() const { return _jumpOffset; }
        Hook&    SetJumpOffset(uint32_t jumpOffset) {
            _jumpOffset = jumpOffset;
            return *this;
        }
        bool DoesJumpBackToOriginalAddressAtEnd() const {
            return _trampoline_jumpBackToOriginalAddressAtEnd;
        }
        Hook& JumpBackToOriginalAddressAtEnd(bool newBytes_jumpBackToOriginalAddressAtEnd = true) {
            _trampoline_jumpBackToOriginalAddressAtEnd = newBytes_jumpBackToOriginalAddressAtEnd;
            return *this;
        }
        uint32_t GetJumpBackAddress() const { return _detour.GetAddress() + _jumpOffset; }
        bool DoesWriteOriginalBytesAtStart() const { return _trampoline_writeOriginalBytesAtStart; }
        Hook& WriteOriginalBytesAtStart(bool newBytes_writeOriginalBytesAtStart = true) {
            _trampoline_writeOriginalBytesAtStart = newBytes_writeOriginalBytesAtStart;
            return *this;
        }
        //////////////////////////////
    };
}
