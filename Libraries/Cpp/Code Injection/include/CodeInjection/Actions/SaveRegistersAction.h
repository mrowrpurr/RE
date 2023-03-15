#pragma once

#include <Memory.h>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "../InjectionAction.h"
#include "../Registers.h"

namespace CodeInjection::Actions {

    struct SaveRegistersActionParams {
        uintptr_t                    address = 0;
        std::string                  addressVariable;
        bool                         x64            = false;
        bool                         writeProtected = false;
        std::unordered_set<Register> registers;
        uintptr_t                    eaxStorageAddress = 0;
        std::string                  eaxStorageAddressVariable;
        uintptr_t                    ebxStorageAddress = 0;
        std::string                  ebxStorageAddressVariable;
        uintptr_t                    ecxStorageAddress = 0;
        std::string                  ecxStorageAddressVariable;
        uintptr_t                    edxStorageAddress = 0;
        std::string                  edxStorageAddressVariable;
        uintptr_t                    esiStorageAddress = 0;
        std::string                  esiStorageAddressVariable;
        uintptr_t                    ediStorageAddress = 0;
        std::string                  ediStorageAddressVariable;
        uintptr_t                    ebpStorageAddress = 0;
        std::string                  ebpStorageAddressVariable;
        uintptr_t                    espStorageAddress = 0;
        std::string                  espStorageAddressVariable;
        uintptr_t                    raxStorageAddress = 0;
        std::string                  raxStorageAddressVariable;
        uintptr_t                    rbxStorageAddress = 0;
        std::string                  rbxStorageAddressVariable;
        uintptr_t                    rcxStorageAddress = 0;
        std::string                  rcxStorageAddressVariable;
        uintptr_t                    rdxStorageAddress = 0;
        std::string                  rdxStorageAddressVariable;
        uintptr_t                    rsiStorageAddress = 0;
        std::string                  rsiStorageAddressVariable;
        uintptr_t                    rdiStorageAddress = 0;
        std::string                  rdiStorageAddressVariable;
        uintptr_t                    rbpStorageAddress = 0;
        std::string                  rbpStorageAddressVariable;
        uintptr_t                    rspStorageAddress = 0;
        std::string                  rspStorageAddressVariable;
        uintptr_t                    r8StorageAddress = 0;
        std::string                  r8StorageAddressVariable;
        uintptr_t                    r9StorageAddress = 0;
        std::string                  r9StorageAddressVariable;
        uintptr_t                    r10StorageAddress = 0;
        std::string                  r10StorageAddressVariable;
        uintptr_t                    r11StorageAddress = 0;
        std::string                  r11StorageAddressVariable;
        uintptr_t                    r12StorageAddress = 0;
        std::string                  r12StorageAddressVariable;
        uintptr_t                    r13StorageAddress = 0;
        std::string                  r13StorageAddressVariable;
        uintptr_t                    r14StorageAddress = 0;
        std::string                  r14StorageAddressVariable;
        uintptr_t                    r15StorageAddress = 0;
        std::string                  r15StorageAddressVariable;
        uintptr_t                    xmm0StorageAddress = 0;
        std::string                  xmm0StorageAddressVariable;
        uintptr_t                    xmm1StorageAddress = 0;
        std::string                  xmm1StorageAddressVariable;
        uintptr_t                    xmm2StorageAddress = 0;
        std::string                  xmm2StorageAddressVariable;
        uintptr_t                    xmm3StorageAddress = 0;
        std::string                  xmm3StorageAddressVariable;
        uintptr_t                    xmm4StorageAddress = 0;
        std::string                  xmm4StorageAddressVariable;
        uintptr_t                    xmm5StorageAddress = 0;
        std::string                  xmm5StorageAddressVariable;
        uintptr_t                    xmm6StorageAddress = 0;
        std::string                  xmm6StorageAddressVariable;
        uintptr_t                    xmm7StorageAddress = 0;
        std::string                  xmm7StorageAddressVariable;
        uintptr_t                    xmm8StorageAddress = 0;
        std::string                  xmm8StorageAddressVariable;
        uintptr_t                    xmm9StorageAddress = 0;
        std::string                  xmm9StorageAddressVariable;
        uintptr_t                    xmm10StorageAddress = 0;
        std::string                  xmm10StorageAddressVariable;
        uintptr_t                    xmm11StorageAddress = 0;
        std::string                  xmm11StorageAddressVariable;
        uintptr_t                    xmm12StorageAddress = 0;
        std::string                  xmm12StorageAddressVariable;
        uintptr_t                    xmm13StorageAddress = 0;
        std::string                  xmm13StorageAddressVariable;
        uintptr_t                    xmm14StorageAddress = 0;
        std::string                  xmm14StorageAddressVariable;
        uintptr_t                    xmm15StorageAddress = 0;
        std::string                  xmm15StorageAddressVariable;
    };

    class SaveRegistersAction : public InjectionAction {
        SaveRegistersActionParams _params;

    public:
        SaveRegistersAction(SaveRegistersActionParams params) : _params(params) {}

        bool IsWriteProtected(std::shared_ptr<InjectionVariables> vars) {
            return _params.writeProtected || CurrentAddressWriteProtected;
        }

        uintptr_t GetAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.addressVariable.empty()) return vars->Get<uintptr_t>(_params.addressVariable);
            else if (_params.address != 0) return _params.address;
            else if (ActionCurrentAddress != 0) return ActionCurrentAddress;
            else throw std::runtime_error("SaveRegistersAction: No address specified");
        }

        std::vector<uint8_t> GetBytes(std::shared_ptr<InjectionVariables> vars) {
            Memory::Bytes bytes;
            if (_params.registers.contains(Register::EAX)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.eaxStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.eaxStorageAddressVariable);
                else if (_params.eaxStorageAddress != 0) registerStorageAddress = _params.eaxStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::EAX);
                bytes.AddBytes(Registers::Instructions::Store::EAX);
                bytes.AddAddress(registerStorageAddress);
            }
            // TODO ADD THE OTHER REGISTERS AFTER TESTING EAX
            return bytes.GetBytes();
        }

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return GetBytes(vars).size(); }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto address          = GetAddress(vars);
            auto bytes            = GetBytes(vars);
            auto isWriteProtected = IsWriteProtected(vars);

            Log("SaveRegistersAction: Saving Registers (x64? {}) using {} bytes to 0x{:x} (Protected: {})", _params.x64,
                bytes.size(), address, isWriteProtected);

            if (isWriteProtected) Memory::WriteProtectedBytes(address, bytes);
            else Memory::WriteBytes(address, bytes);
        }
    };
}