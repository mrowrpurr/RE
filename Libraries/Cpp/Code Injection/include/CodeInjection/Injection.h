#pragma once

#include <Memory.h>
#include <StatefulApp.h>

#include <string>

#include "CodeInjection/Actions/ReadBytes.h"
#include "CodeInjection/Actions/WriteBytes.h"
#include "CodeInjection/Actions/WriteBytesByVar.h"
#include "CodeInjection/Actions/WriteProtectedBytes.h"
#include "CodeInjection/Actions/WriteProtectedBytesByVar.h"

namespace CodeInjection {

    class Injection {
        constexpr static const char* VARNAME_ADDRESS = "address";

        std::string      _name;
        StatefulApp::App _app;

    public:
        explicit Injection(const std::string& name) : _name(name) {}

        Injection& SetAddress(uintptr_t address) {
            _app.Set<uintptr_t>(VARNAME_ADDRESS, address);
            return *this;
        }
        uintptr_t GetAddress() const { return _app.Get<uintptr_t>(VARNAME_ADDRESS); }

        Injection& Begin(const std::string& name) {
            _app.ConfigureState(name);
            return *this;
        }
        Injection& End() {
            _app.EndConfigure();
            return *this;
        }

        Injection& BeginInstall() { return Begin("Install"); }
        Injection& EndInstall() { return End(); }

        Injection& BeginUninstall() { return Begin("Uninstall"); }
        Injection& EndUninstall() { return End(); }

        Injection& Install() {
            _app.Goto("Install");
            return *this;
        }
        Injection& Uninstall() {
            _app.Goto("Uninstall");
            return *this;
        }

        template <size_t N>
        Injection& SaveBytes(const std::string& name) {
            _app.AddAction(ReadBytesAction{name, 0, N});
            return *this;
        }
        std::vector<uint8_t> GetSavedBytes(const std::string& name) const {
            return _app.Get<std::vector<uint8_t>>(name);
        }
        Injection& WriteBytes(const std::vector<uint8_t>& bytes) {
            _app.AddAction(WriteBytesAction{bytes});
            return *this;
        }
        Injection& WriteBytesByVar(const std::string& variableName) {
            _app.AddAction(WriteBytesByVarAction{variableName});
            return *this;
        }
        Injection& WriteProtectedBytes(const std::vector<uint8_t>& bytes) {
            _app.AddAction(WriteProtectedBytesAction{bytes});
            return *this;
        }
        Injection& WriteProtectedBytesByVar(const std::string& variableName) {
            _app.AddAction(WriteProtectedBytesByVarAction{variableName});
            return *this;
        }
    };
}
