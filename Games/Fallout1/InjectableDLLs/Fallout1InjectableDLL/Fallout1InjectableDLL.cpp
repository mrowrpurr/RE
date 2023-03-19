#include <Assembly.h>
#include <CodeInjection.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <Memory.h>
#include <StringFormatting.h>
#include <UserInterface.h>

#include <cstdint>
#include <limits>
#include <string>
#include <thread>

//
#include <luajit/lua.hpp>

//
#include <luabridge3/LuaBridge/LuaBridge.h>

SetLogFilePath("InjectedDLL.log");

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

std::string PathToLuaScript(const std::string& scriptName) {
    auto RE_ProjectPath = std::getenv("RE_PROJECT");
    return string_format(
        "{}/Games/Fallout1/InjectableDLLs/Fallout1InjectableDLL/{}", RE_ProjectPath, scriptName
    );
}

void OutputLuaErrors(lua_State* luaState, int status) {
    if (status == 0) return;
    Output("[LUA ERROR] {}", lua_tostring(luaState, -1));
    lua_pop(luaState, 1);  // remove error message from Lua state
}

struct SomeRandomStruct {
    uint32_t    intA;
    uint32_t    intB;
    const char* text;
};

SomeRandomStruct InstanceOfRandomStruct = {69, 420, "Hello from C++"};

void DoLuaStuff() {
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);
    auto scriptPath = PathToLuaScript("read_from_fallout1_memory.lua");
    auto status     = luaL_dofile(L, scriptPath.c_str());
    OutputLuaErrors(L, status);

    luaL_dostring(
        L,
        string_format("theAddress = 0x{:x}", reinterpret_cast<uintptr_t>(&InstanceOfRandomStruct))
            .c_str()
    );

    if (status != 0) {
        Log("Failed to load Lua script");
        return;
    }

    lua_getglobal(L, "CallMeMaybe");
    status = lua_pcall(L, 0, 1, 0);
    OutputLuaErrors(L, status);

    if (status != 0) {
        Log("Failed to call Lua function");
        return;
    }

    // auto value = lua_tointeger(L, -1);
    auto value = lua_tostring(L, -1);
    lua_pop(L, 1);

    Log("Lua Says: '{}'", value);

    // luabridge::LuaRef callMeMaybe = luabridge::getGlobal(L, "CallMeMaybe");
    // auto              response    = callMeMaybe();
    // auto              value       = response[0].cast<uint32_t>();

    // Log("Response: {}", value);

    Log("Gonna call the Lua function");

    lua_close(L);
}

void SetupHooks() {
    CodeInjection::InjectFunction<11>("Drop Item", 0x46a41c, [](Registers& regs) {
        Output("I am a function and I was called!");
        Output("EAX is {:x}", regs.eax());
        Output("EAX 0x0 is {}", regs.eax(0x0));
        Output("EAX 0x34 0x0 is {:x}", regs.eax({0x34, 0x0}));
        Output("EAX 0x34 0x4 is {}", regs.eax({0x34, 0x4}));
        Output("EAX 0x34 0x0 0x64 is {}", regs.eax({0x34, 0x0, 0x64}));
    });

    CodeInjection::New("Freeze Carry Weight")
        .Configure([](Injection& _) {
            _.Var<uintptr_t>("OverwriteAddress", 0x49ceca);
            _.ReadBytes("OverwriteAddress", "OriginalBytes", 3);
        })
        .OnInstall([](Injection& _) { _.WriteNop("OverwriteAddress", 3); })
        .OnUninstall([](Injection& _) { _.WriteBytes("OverwriteAddress", "OriginalBytes"); });
}

void FollowAndLogMysteriousLinkedList() {
    auto address           = 0x87F9E64;  // From what 0xf1_res.dll+DE6F accesses
    auto nextPointerOffset = 0x98;
    auto identifierOffset  = 0x0;
    auto tileNumberOffset  = 0x4;

    while (address != 0) {
        Log("Address: {:x}", address);

        auto identifier = Memory::Read<uint32_t>(address, identifierOffset);
        Log("Identifier: {}", identifier);

        auto tileNumber = Memory::Read<uint32_t>(address, tileNumberOffset);
        Log("Tile Number: {}", tileNumber);

        address = Memory::Read<uintptr_t>(address, nextPointerOffset);
        Log("Next Address: {:x}", address);
    }
}

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        for (auto [name, injection] : CodeInjection::RegisteredInjections) {
            app.AddButton(string_format("Enable {}", injection->GetName()), [&, injection]() {
                injection->Toggle();
                if (injection->IsInstalled())
                    app.ChangeButtonText(string_format("Disable {}", injection->GetName()));
                else app.ChangeButtonText(string_format("Enable {}", injection->GetName()));
            });
        }
        app.AddButton("Do Lua Stuff", [&]() { DoLuaStuff(); });
        app.AddButton("Follow and Log Mysterious Linked List", [&]() {
            FollowAndLogMysteriousLinkedList();
        });
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    // SetupHooks();
    RunUI();
    CodeInjection::UninstallAll();
    Injected_DLL::EjectDLL();
}
