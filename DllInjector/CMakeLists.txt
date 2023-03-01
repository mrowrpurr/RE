project(DLLInjection VERSION 0.1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_compile_definitions(${PROJECT_NAME} INTERFACE MBCS _MBCS _CRT_SECURE_NO_WARNINGS)

add_subdirectory(Exe)
add_subdirectory(UI)
