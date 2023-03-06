#pragma once

#include <functional>
#include <optional>
#include <stdexcept>
#include <string>

#include "Hooks/Bytes.h"
#include "Hooks/Memory.h"
#include "Hooks/MemoryBytes.h"

namespace Hooks {

    // Represents a hook to a specific address implemented via a JMP
    class Hook {
        constexpr static auto MINIMUM_REPLACE_BYTES_LENGTH = 5;

        std::string                          _name;
        bool                                 _installed = false;
        std::optional<std::function<void()>> _installFunction;
        std::optional<std::function<void()>> _uninstallFunction;
        uint32_t                             _address = 0;
        uint32_t    _addressReplaceBytesCount         = MINIMUM_REPLACE_BYTES_LENGTH;
        Bytes       _addressOriginalReplacedBytes;
        MemoryBytes _targetAddressBytes;
        uint32_t    _jumpOffset = MINIMUM_REPLACE_BYTES_LENGTH;
        uint32_t    _newMemoryAddress;
        MemoryBytes _newBytes;
        bool        _newBytes_writeOriginalBytesAtStart = false;

    public:
        const std::string& GetName() const { return _name; }
        Hook&              SetName(const std::string& name) {
            _name = name;
            return *this;
        }

        bool IsInstalled() const { return _installed; }

        // Set the function to be called when the hook is installed
        Hook& SetInstallFunction(const std::function<void()>& installFunction) {
            _installFunction = installFunction;
            return *this;
        }

        // Set the function to be called when the hook is uninstalled
        Hook& SetUninstallFunction(const std::function<void()>& uninstallFunction) {
            _uninstallFunction = uninstallFunction;
            return *this;
        }

        void Install() {
            if (_installFunction.has_value()) {
                _installFunction.value()();
                return;
            }
            if (_address == 0) throw std::runtime_error("Hook address not set");
            WriteNewBytes();
            OverwriteOriginalBytes();
        }

        void Uninstall() {
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

        uint32_t GetAddress() const { return _address; }
        Hook&    SetAddress(uint32_t address) {
            _address = address;
            return *this;
        }

        uint32_t GetAddressReplaceBytesCount() const { return _addressReplaceBytesCount; }
        Hook&    SetAddressReplaceBytesCount(uint32_t addressReplaceBytesCount) {
            _addressReplaceBytesCount = addressReplaceBytesCount;
            return *this;
        }

        Bytes& GetAddressOriginalReplacedBytes() { return _addressOriginalReplacedBytes; }
        Hook&  SetAddressOriginalReplacedBytes(std::vector<uint8_t> addressOriginalReplacedBytes) {
            _addressOriginalReplacedBytes = Bytes{addressOriginalReplacedBytes};
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

        uint32_t GetJumpBackAddress() const { return _address + _jumpOffset; }

        bool  DoesWriteOriginalBytesAtStart() const { return _newBytes_writeOriginalBytesAtStart; }
        Hook& WriteOriginalBytesAtStart(bool newBytes_writeOriginalBytesAtStart = true) {
            _newBytes_writeOriginalBytesAtStart = newBytes_writeOriginalBytesAtStart;
            return *this;
        }

        Bytes& GetOriginalBytes() { return _addressOriginalReplacedBytes; }
        Bytes ReadOriginalBytes() { return Memory::ReadBytes(_address, _addressReplaceBytesCount); }

        void WriteNewBytes() {
            if (_newBytes_writeOriginalBytesAtStart) {
                _newBytes.WriteBytes(ReadOriginalBytes());
            }
            _newBytes.WriteJmp(GetJumpBackAddress());
        }

        void OverwriteOriginalBytes() {
            _targetAddressBytes.SetAddress(_address);
            _targetAddressBytes.WriteProtectedJmp(_newBytes.GetAddress());
        }
    };
}

// // Get the original bytes
// _addressOriginalReplacedBytes = ReadOriginalBytes();

// // Get a reference to the bytes we're going to overwrite
// _targetAddressBytes.SetAddress(_address);

// // Setup the bytes to overwrite
// _targetAddressBytes.SetBytes(GenerateOverwriteJumpBytes(_newBytes.GetAddress()));

// // Overwrite the original bytes with a JMP to the new bytes
// _targetAddressBytes.WriteProtected();