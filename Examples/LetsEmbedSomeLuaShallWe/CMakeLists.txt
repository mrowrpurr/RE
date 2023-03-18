project(LetsEmbedSomeLuaShallWe)

find_path(LUABRIDGE3_INCLUDE_DIRS "luabridge3/LuaBridge/LuaBridge.h")
find_package(Lua REQUIRED)

add_executable("${PROJECT_NAME}" LetsEmbedSomeLuaShallWe.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${LUABRIDGE3_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE StringFormatting ${LUA_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE _HAS_CXX17) # for LuaBridge3
