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

    struct RestoreRegistersActionParams {
        uintptr_t                    address = 0;
        std::string                  addressVariable;
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

    class RestoreRegistersAction : public InjectionAction {
        RestoreRegistersActionParams _params;

    public:
        RestoreRegistersAction(RestoreRegistersActionParams params) : _params(params) {}

        bool IsWriteProtected(std::shared_ptr<InjectionVariables> vars) {
            return _params.writeProtected || CurrentAddressWriteProtected;
        }

        uintptr_t GetAddress(std::shared_ptr<InjectionVariables> vars) {
            if (!_params.addressVariable.empty()) return vars->Get<uintptr_t>(_params.addressVariable);
            else if (_params.address != 0) return _params.address;
            else if (ActionCurrentAddress != 0) return ActionCurrentAddress;
            else throw std::runtime_error("RestoreRegistersAction: No address specified");
        }

        std::vector<uint8_t> GetBytes(std::shared_ptr<InjectionVariables> vars) {
            Memory::Bytes bytes;
            if (_params.registers.contains(Register::EAX)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.eaxStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.eaxStorageAddressVariable);
                else if (_params.eaxStorageAddress != 0) registerStorageAddress = _params.eaxStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::EAX);
                bytes.AddBytes(Registers::Instructions::Restore::EAX);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::EBX)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.ebxStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.ebxStorageAddressVariable);
                else if (_params.ebxStorageAddress != 0) registerStorageAddress = _params.ebxStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::EBX);
                bytes.AddBytes(Registers::Instructions::Restore::EBX);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::ECX)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.ecxStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.ecxStorageAddressVariable);
                else if (_params.ecxStorageAddress != 0) registerStorageAddress = _params.ecxStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::ECX);
                bytes.AddBytes(Registers::Instructions::Restore::ECX);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::EDX)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.edxStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.edxStorageAddressVariable);
                else if (_params.edxStorageAddress != 0) registerStorageAddress = _params.edxStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::EDX);
                bytes.AddBytes(Registers::Instructions::Restore::EDX);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::ESI)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.esiStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.esiStorageAddressVariable);
                else if (_params.esiStorageAddress != 0) registerStorageAddress = _params.esiStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::ESI);
                bytes.AddBytes(Registers::Instructions::Restore::ESI);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::EDI)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.ediStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.ediStorageAddressVariable);
                else if (_params.ediStorageAddress != 0) registerStorageAddress = _params.ediStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::EDI);
                bytes.AddBytes(Registers::Instructions::Restore::EDI);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::EBP)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.ebpStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.ebpStorageAddressVariable);
                else if (_params.ebpStorageAddress != 0) registerStorageAddress = _params.ebpStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::EBP);
                bytes.AddBytes(Registers::Instructions::Restore::EBP);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::ESP)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.espStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.espStorageAddressVariable);
                else if (_params.espStorageAddress != 0) registerStorageAddress = _params.espStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::ESP);
                bytes.AddBytes(Registers::Instructions::Restore::ESP);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::RAX)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.raxStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.raxStorageAddressVariable);
                else if (_params.raxStorageAddress != 0) registerStorageAddress = _params.raxStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::RAX);
                bytes.AddBytes(Registers::Instructions::Restore::RAX);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::RBX)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.rbxStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.rbxStorageAddressVariable);
                else if (_params.rbxStorageAddress != 0) registerStorageAddress = _params.rbxStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::RBX);
                bytes.AddBytes(Registers::Instructions::Restore::RBX);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::RCX)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.rcxStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.rcxStorageAddressVariable);
                else if (_params.rcxStorageAddress != 0) registerStorageAddress = _params.rcxStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::RCX);
                bytes.AddBytes(Registers::Instructions::Restore::RCX);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::RDX)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.rdxStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.rdxStorageAddressVariable);
                else if (_params.rdxStorageAddress != 0) registerStorageAddress = _params.rdxStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::RDX);
                bytes.AddBytes(Registers::Instructions::Restore::RDX);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::RSI)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.rsiStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.rsiStorageAddressVariable);
                else if (_params.rsiStorageAddress != 0) registerStorageAddress = _params.rsiStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::RSI);
                bytes.AddBytes(Registers::Instructions::Restore::RSI);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::RDI)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.rdiStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.rdiStorageAddressVariable);
                else if (_params.rdiStorageAddress != 0) registerStorageAddress = _params.rdiStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::RDI);
                bytes.AddBytes(Registers::Instructions::Restore::RDI);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::RBP)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.rbpStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.rbpStorageAddressVariable);
                else if (_params.rbpStorageAddress != 0) registerStorageAddress = _params.rbpStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::RBP);
                bytes.AddBytes(Registers::Instructions::Restore::RBP);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::RSP)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.rspStorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.rspStorageAddressVariable);
                else if (_params.rspStorageAddress != 0) registerStorageAddress = _params.rspStorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::RSP);
                bytes.AddBytes(Registers::Instructions::Restore::RSP);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::R8)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.r8StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.r8StorageAddressVariable);
                else if (_params.r8StorageAddress != 0) registerStorageAddress = _params.r8StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::R8);
                bytes.AddBytes(Registers::Instructions::Restore::R8);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::R9)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.r9StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.r9StorageAddressVariable);
                else if (_params.r9StorageAddress != 0) registerStorageAddress = _params.r9StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::R9);
                bytes.AddBytes(Registers::Instructions::Restore::R9);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::R10)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.r10StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.r10StorageAddressVariable);
                else if (_params.r10StorageAddress != 0) registerStorageAddress = _params.r10StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::R10);
                bytes.AddBytes(Registers::Instructions::Restore::R10);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::R11)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.r11StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.r11StorageAddressVariable);
                else if (_params.r11StorageAddress != 0) registerStorageAddress = _params.r11StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::R11);
                bytes.AddBytes(Registers::Instructions::Restore::R11);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::R12)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.r12StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.r12StorageAddressVariable);
                else if (_params.r12StorageAddress != 0) registerStorageAddress = _params.r12StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::R12);
                bytes.AddBytes(Registers::Instructions::Restore::R12);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::R13)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.r13StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.r13StorageAddressVariable);
                else if (_params.r13StorageAddress != 0) registerStorageAddress = _params.r13StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::R13);
                bytes.AddBytes(Registers::Instructions::Restore::R13);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::R14)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.r14StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.r14StorageAddressVariable);
                else if (_params.r14StorageAddress != 0) registerStorageAddress = _params.r14StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::R14);
                bytes.AddBytes(Registers::Instructions::Restore::R14);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::R15)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.r15StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.r15StorageAddressVariable);
                else if (_params.r15StorageAddress != 0) registerStorageAddress = _params.r15StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::R15);
                bytes.AddBytes(Registers::Instructions::Restore::R15);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM0)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm0StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm0StorageAddressVariable);
                else if (_params.xmm0StorageAddress != 0) registerStorageAddress = _params.xmm0StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM0);
                bytes.AddBytes(Registers::Instructions::Restore::XMM0);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM1)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm1StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm1StorageAddressVariable);
                else if (_params.xmm1StorageAddress != 0) registerStorageAddress = _params.xmm1StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM1);
                bytes.AddBytes(Registers::Instructions::Restore::XMM1);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM2)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm2StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm2StorageAddressVariable);
                else if (_params.xmm2StorageAddress != 0) registerStorageAddress = _params.xmm2StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM2);
                bytes.AddBytes(Registers::Instructions::Restore::XMM2);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM3)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm3StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm3StorageAddressVariable);
                else if (_params.xmm3StorageAddress != 0) registerStorageAddress = _params.xmm3StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM3);
                bytes.AddBytes(Registers::Instructions::Restore::XMM3);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM4)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm4StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm4StorageAddressVariable);
                else if (_params.xmm4StorageAddress != 0) registerStorageAddress = _params.xmm4StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM4);
                bytes.AddBytes(Registers::Instructions::Restore::XMM4);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM5)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm5StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm5StorageAddressVariable);
                else if (_params.xmm5StorageAddress != 0) registerStorageAddress = _params.xmm5StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM5);
                bytes.AddBytes(Registers::Instructions::Restore::XMM5);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM6)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm6StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm6StorageAddressVariable);
                else if (_params.xmm6StorageAddress != 0) registerStorageAddress = _params.xmm6StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM6);
                bytes.AddBytes(Registers::Instructions::Restore::XMM6);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM7)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm7StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm7StorageAddressVariable);
                else if (_params.xmm7StorageAddress != 0) registerStorageAddress = _params.xmm7StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM7);
                bytes.AddBytes(Registers::Instructions::Restore::XMM7);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM8)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm8StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm8StorageAddressVariable);
                else if (_params.xmm8StorageAddress != 0) registerStorageAddress = _params.xmm8StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM8);
                bytes.AddBytes(Registers::Instructions::Restore::XMM8);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM9)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm9StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm9StorageAddressVariable);
                else if (_params.xmm9StorageAddress != 0) registerStorageAddress = _params.xmm9StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM9);
                bytes.AddBytes(Registers::Instructions::Restore::XMM9);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM10)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm10StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm10StorageAddressVariable);
                else if (_params.xmm10StorageAddress != 0) registerStorageAddress = _params.xmm10StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM10);
                bytes.AddBytes(Registers::Instructions::Restore::XMM10);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM11)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm11StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm11StorageAddressVariable);
                else if (_params.xmm11StorageAddress != 0) registerStorageAddress = _params.xmm11StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM11);
                bytes.AddBytes(Registers::Instructions::Restore::XMM11);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM12)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm12StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm12StorageAddressVariable);
                else if (_params.xmm12StorageAddress != 0) registerStorageAddress = _params.xmm12StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM12);
                bytes.AddBytes(Registers::Instructions::Restore::XMM12);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM13)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm13StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm13StorageAddressVariable);
                else if (_params.xmm13StorageAddress != 0) registerStorageAddress = _params.xmm13StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM13);
                bytes.AddBytes(Registers::Instructions::Restore::XMM13);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM14)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm14StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm14StorageAddressVariable);
                else if (_params.xmm14StorageAddress != 0) registerStorageAddress = _params.xmm14StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM14);
                bytes.AddBytes(Registers::Instructions::Restore::XMM14);
                bytes.AddAddress(registerStorageAddress);
            }
            if (_params.registers.contains(Register::XMM15)) {
                uintptr_t registerStorageAddress = 0;
                if (!_params.xmm15StorageAddressVariable.empty())
                    registerStorageAddress = vars->Get<uintptr_t>(_params.xmm15StorageAddressVariable);
                else if (_params.xmm15StorageAddress != 0) registerStorageAddress = _params.xmm15StorageAddress;
                else registerStorageAddress = reinterpret_cast<uintptr_t>(&Registers::CurrentValues::XMM15);
                bytes.AddBytes(Registers::Instructions::Restore::XMM15);
                bytes.AddAddress(registerStorageAddress);
            }
            return bytes.GetBytes();
        }

        size_t GetByteCount(std::shared_ptr<InjectionVariables> vars) override { return GetBytes(vars).size(); }

        void Perform(std::shared_ptr<InjectionVariables> vars) override {
            auto address          = GetAddress(vars);
            auto bytes            = GetBytes(vars);
            auto isWriteProtected = IsWriteProtected(vars);

            Log("RestoreRegistersAction: Restoring Registers using {} bytes to 0x{:x} (Protected: {})", bytes.size(),
                address, isWriteProtected);

            if (isWriteProtected) Memory::WriteProtected(address, bytes);
            else Memory::Write(address, bytes);
        }
    };
}