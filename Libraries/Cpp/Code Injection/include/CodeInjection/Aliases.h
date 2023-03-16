#pragma once

#include <Assembly.h>

#include "CodeInjection/CodeInjection.h"
#include "CodeInjection/Registers.h"

typedef CodeInjection::Injection                  Injection;
typedef CodeInjection::Register                   Register;
typedef CodeInjection::Registers::RegistersReader Registers;
typedef Xbyak::CodeGenerator                      AssemblyCode;
