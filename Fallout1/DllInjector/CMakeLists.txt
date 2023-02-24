cmake_minimum_required(VERSION 3.5)

project(LibraryToInject VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(LibraryToInject SHARED LibraryToInject.cpp)
target_compile_definitions(LibraryToInject PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX UNICODE _UNICODE MBCS _MBCS _CRT_SECURE_NO_WARNINGS)
