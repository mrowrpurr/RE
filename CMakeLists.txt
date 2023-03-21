cmake_minimum_required(VERSION 3.25.1)

project(ReverseEngineeringPlayground LANGUAGES CXX)

if(${CMAKE_EXE_LINKER_FLAGS} STREQUAL "/machine:x64")
    set (ARCH "x64")
else()
    set (ARCH "x86")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

message("CMake bin directory is ${CMAKE_BINARY_DIR}")

add_subdirectory(Libraries)
add_subdirectory(Examples)
add_subdirectory(Tools)
add_subdirectory(ModdingFramework)
add_subdirectory(Games)
