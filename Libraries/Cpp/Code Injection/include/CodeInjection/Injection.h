#pragma once

#include <Memory.h>
#include <StatefulApp.h>
#include <stdint.h>

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "CodeInjection/Actions/AllocateMemoryAction.h"
#include "CodeInjection/Actions/ByteWriterActionGroup.h"
#include "CodeInjection/Actions/FreeMemoryAction.h"
#include "CodeInjection/Actions/ReadBytesAction.h"
#include "CodeInjection/Actions/RunFunctionAction.h"
#include "CodeInjection/Actions/WriteBytesAction.h"


#ifdef CODE_INJECTION_XBYAK
// #include "CodeInjection/Actions/WriteAssembly.h"
// #include "CodeInjection/Actions/WriteProtectedAssembly.h"
#endif

namespace CodeInjection {

    class Injection {
        constexpr static const char* VARNAME_ADDRESS = "address";

        std::string      _name;
        StatefulApp::App _app;

    public:
        explicit Injection(const std::string& name) : _name(name) {}

        /**
         * "Configure" block (just for semantics)
         */

        Injection& Configure(std::function<void(Injection&)> function) {
            function(*this);
            return *this;
        }

        /**
         * Variables
         */

        template <typename T>
        Injection& Set(const std::string& name, T value) {
            _app.Set<T>(name, value);
            return *this;
        }
        template <typename T>
        Injection& Set(const std::string& name) {
            _app.Set<T>(name);
            return *this;
        }
        Injection& SetBytes(const std::string& name, const std::vector<uint8_t>& bytes) {
            _app.Set<Memory::Bytes>(name, Memory::Bytes{bytes});
            return *this;
        }

        /**
         * States
         */

        Injection& BeginConfigureState(const std::string& name) {
            _app.ConfigureState(name);
            return *this;
        }
        Injection& EndConfigureState() {
            _app.EndConfigure();
            return *this;
        }
        Injection& On(const std::string& name, std::function<void(Injection&)> function) {
            BeginConfigureState(name);
            function(*this);
            EndConfigureState();
            return *this;
        }
        Injection& OnInstall(std::function<void(Injection&)> function) {
            return On("Install", function);
        }
        Injection& OnUninstall(std::function<void(Injection&)> function) {
            return On("Uninstall", function);
        }
        Injection& Install() {
            _app.Goto("Install");
            return *this;
        }
        Injection& Uninstall() {
            _app.Goto("Uninstall");
            return *this;
        }

        /**
         * Run Actions
         */

        Injection& Run(const std::function<void()>& function) {
            _app.AddAction(RunFunctionAction{function});
            return *this;
        }
        Injection& Run(const std::function<void(StatefulApp::Variables&)>& function) {
            _app.AddAction(RunFunctionAction{function});
            return *this;
        }

        /**
         * Memory Actions
         */

        Injection& AllocateMemory(
            const std::string&                                 addressVariableName,
            std::function<void(AllocatedMemoryActionBuilder&)> builderFunction
        ) {
            _app.AddAction(AllocateMemoryAction{addressVariableName, builderFunction});
            return *this;
        }

        Injection& FreeMemory(const std::string& addressVariableName) {
            _app.AddAction(FreeMemoryAction{addressVariableName});
            return *this;
        }

        /**
         * Byte Actions
         */

        Injection& ReadBytes(
            const std::string& inputAddressVariable, const std::string& outputBytesVariable,
            size_t byteCount
        ) {
            _app.AddAction(ReadBytesAction{inputAddressVariable, outputBytesVariable, byteCount});
            return *this;
        }
        Injection& WriteBytes(
            const std::string& addressVariable, const std::string& bytesVariable
        ) {
            _app.AddAction(WriteBytesAction{addressVariable, bytesVariable});
            return *this;
        }
        Injection& WriteProtectedBytes(
            const std::string& addressVariable, const std::string& bytesVariable
        ) {
            _app.AddAction(WriteBytesAction{addressVariable, bytesVariable}.Protected());
            return *this;
        }

#ifdef CODE_INJECTION_XBYAK

        /**
         * Xbyak Actions
         */

        // Injection& WriteAssembly(const std::function<void(Xbyak::CodeGenerator&)>&
        // assemblyGenerator ) {
        //     _app.AddAction(WriteProtectedAssemblyAction{assemblyGenerator});
        //     return *this;
        // }
#endif
    };
}
