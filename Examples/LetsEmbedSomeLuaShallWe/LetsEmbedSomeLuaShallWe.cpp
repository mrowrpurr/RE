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
    std::cout << "[END]" << std::endl;
}
