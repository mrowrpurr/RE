project(Fallout1InjectableDLL)

cmake_policy(SET CMP0079 NEW)
set(Boost_NO_WARN_NEW_VERSIONS 1)

find_package(ZLIB REQUIRED)

set(DAT_UNPACKER_LIB "$ENV{DAT_UNPACKER_LIB}")
message(STATUS "DAT unpacker path: ${DAT_UNPACKER_LIB}")

add_subdirectory("${DAT_UNPACKER_LIB}" build SYSTEM)

add_library(${PROJECT_NAME} SHARED Fallout1InjectableDLL.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE dat-unpacker Injected_DLL Memory Assembly CodeInjection UserInterface Logging)
