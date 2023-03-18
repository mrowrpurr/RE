#include <StringFormatting.h>

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
    std::cout << "[BEGIN]" << std::endl;
    Call_Lua_String_Lua_From_Cpp();
    Call_Lua_File_Script_From_Cpp();
    Call_Cpp_Function_From_Lua();
    std::cout << "[END]" << std::endl;
}
