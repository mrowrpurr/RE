#pragma once

#ifdef CODE_INJECTION_XBYAK
    #include <xbyak/xbyak.h>
#endif

#include <Memory.h>

#include <any>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "CodeInjecting/CodeInjectionAction.h"

namespace CodeInjecting {
    class CodeInjection {
        std::string                                                       _name = "";
        std::unordered_map<std::string, std::any>                         _variables;
        std::unordered_map<std::string, std::vector<CodeInjectionAction>> _stateDefinitions;
        std::string                                                       _currentState = "";
        Memory::MemoryWriter                                              _memoryCursor;

    public:
        explicit CodeInjection(const std::string& name) : _name(name) {}

        const std::string& GetName() const { return _name; }

        void AddAction(const std::string& stateName, CodeInjectionAction action) {
            if (_stateDefinitions.contains(stateName))
                _stateDefinitions[stateName].emplace_back(std::move(action));
            else
                _stateDefinitions[stateName] = {std::move(action)};
        }

        // template <typename T>
        // CodeInjection& SetVariable(const std::string& name, T value) {
        //     _variables[name] = value;
        //     return *this;
        // }

        // template <typename T>
        // T GetVariable(const std::string& name) {
        //     return std::any_cast<T>(_variables[name]);
        // }
    };
}