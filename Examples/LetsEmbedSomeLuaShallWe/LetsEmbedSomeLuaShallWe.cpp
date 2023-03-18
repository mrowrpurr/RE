#include <Logging.h>
#include <StringFormatting.h>

// Learn how to make our own 'libraries'
// to require for autocompletion

extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

std::string PathToScript(const std::string& scriptName) {
    return string_format("../../../../Examples/LetsEmbedSomeLuaShallWe/scripts/{}", scriptName);
}

#include <luabridge3/LuaBridge/LuaBridge.h>

#include <iostream>

void report_lua_errors(lua_State* luaState, int status) {
    if (status == 0) return;
    std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;
    lua_pop(luaState, 1);  // remove error message from Lua state
}

// void Delegate_Event_Objects_To_Loaded_Lua_State() {
//     auto scriptPath = PathToScript("Listen_for_events.lua");
//     lua_State* L          = luaL_newstate();
//     luaL_openlibs(L);
//     //
// }

std::unordered_map<std::string, std::string> _eventListeners;

void RegisterEventListener(const std::string& eventName, const std::string& listenerName) {
    Log("Registering event listener '{}' for event '{}'", listenerName, eventName);
    _eventListeners[eventName] = listenerName;
}
void DelegateEvent(lua_State* L, const std::string& eventName, const std::string& eventPayload) {
    Log("Delegating event '{}' with payload '{}'", eventName, eventPayload);
    auto listenerName = _eventListeners[eventName];
    if (listenerName.empty()) return;

    Log("Calling listener '{}' for event '{}' with payload '{}'", listenerName, eventName,
        eventPayload);
    auto gotFunctionOk   = lua_getglobal(L, listenerName.c_str());
    auto pushedStringOk  = lua_pushstring(L, eventPayload.c_str());
    auto eventCallResult = lua_pcall(L, 1, 0, 0);
    report_lua_errors(L, eventCallResult);
}

void Delegate_Simple_Strings_To_Loaded_Lua_State() {
    auto       scriptPath = PathToScript("Listen_For_Simple_String_Events.lua");
    lua_State* L          = luaL_newstate();
    luaL_openlibs(L);
    auto status = luaL_dofile(L, scriptPath.c_str());
    report_lua_errors(L, status);

    // Expose RegisterEventListener to Lua
    luabridge::getGlobalNamespace(L).addFunction("onEvent", RegisterEventListener);

    lua_getglobal(L, "plugin");
    auto pluginCallResult = lua_pcall(L, 0, 0, 0);
    report_lua_errors(L, pluginCallResult);

    // Delegate Bark Event
    DelegateEvent(L, "Bark", "Woof, from C++ string 'event'!");

    // Delegate Butts Event
    DelegateEvent(L, "Butts", "Butts, from C++ string 'event'!");

    //
    lua_close(L);
}

class Dog {
    std::string _name;

public:
    Dog(const std::string& name) : _name(name) {}
    std::string GetName() const { return _name; }
    void        Bark() const { Log("[C++ STDOUT] Woof, my name is {}", _name); }
};

void Construct_Cpp_Dog_Class_From_Lua() {
    auto       scriptPath = PathToScript("Construct_Cpp_Class.lua");
    lua_State* L          = luaL_newstate();
    luaL_openlibs(L);

    // Make C++ class Dog available to Lua
    luabridge::getGlobalNamespace(L)
        .beginNamespace("Animals")
        .beginClass<Dog>("Dog")
        .addConstructor<void (*)(const std::string&)>()
        .addFunction("Bark", &Dog::Bark)
        .addFunction("GetName", &Dog::GetName)
        .endClass()
        .endNamespace();

    auto status = luaL_dofile(L, scriptPath.c_str());
    report_lua_errors(L, status);
    lua_close(L);
}

int Cpp_Function_To_Call_From_Lua() { return 69; }

void Call_Cpp_Function_From_Lua() {
    auto       scriptPath = PathToScript("Call_Cpp_Function.lua");
    lua_State* L          = luaL_newstate();
    luaL_openlibs(L);

    // Make C++ function Cpp_Function_To_Call_From_Lua available to Lua
    luabridge::getGlobalNamespace(L)
        .beginNamespace("Cpp")
        .addFunction("Cpp_Function_To_Call_From_Lua", Cpp_Function_To_Call_From_Lua)
        .endNamespace();

    auto status = luaL_dofile(L, scriptPath.c_str());
    report_lua_errors(L, status);
    lua_close(L);
}

void Call_Lua_String_Lua_From_Cpp() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dostring(L, "print('Hello, from a Lua string!')");
    lua_close(L);
}

void Call_Lua_File_Script_From_Cpp() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, PathToScript("HelloWorld.lua").c_str());
    lua_close(L);
}

int main() {
    Log("[BEGIN]");
    Call_Lua_String_Lua_From_Cpp();
    Call_Lua_File_Script_From_Cpp();
    Call_Cpp_Function_From_Lua();
    Construct_Cpp_Dog_Class_From_Lua();
    Delegate_Simple_Strings_To_Loaded_Lua_State();
    Log("[END]");
}
