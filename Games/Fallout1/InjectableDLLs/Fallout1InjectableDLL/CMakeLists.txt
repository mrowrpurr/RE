project(Fallout1InjectableDLL)

cmake_policy(SET CMP0079 NEW)
set(Boost_NO_WARN_NEW_VERSIONS 1)

find_package(ZLIB REQUIRED)
find_path(LUABRIDGE3_INCLUDE_DIRS "LuaBridge/Array.h")
find_package(LuaJIT REQUIRED)
set(LUAJIT_LIB_PATH "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/lib/lua51.lib")

set(DAT_UNPACKER_LIB "$ENV{DAT_UNPACKER_LIB}")
message(STATUS "DAT unpacker path: ${DAT_UNPACKER_LIB}")

add_subdirectory("${DAT_UNPACKER_LIB}" build SYSTEM)

add_library(${PROJECT_NAME} SHARED Fallout1InjectableDLL.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE . "${LUA_INCLUDE_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE ${LUABRIDGE3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE "${LUAJIT_LIB_PATH}" dat-unpacker Injected_DLL Memory Assembly CodeInjection UserInterface Logging)
target_compile_definitions(${PROJECT_NAME} PRIVATE _HAS_CXX17) # for LuaBridge3
