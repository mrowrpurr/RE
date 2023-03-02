cmake_minimum_required(VERSION 3.2)

project(FalloutLib VERSION 0.1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_definitions(${PROJECT_NAME} INTERFACE WIN32_LEAN_AND_MEAN NOMINMAX UNICODE _UNICODE MBCS _MBCS _CRT_SECURE_NO_WARNINGS)

# TODO: Export / Install
