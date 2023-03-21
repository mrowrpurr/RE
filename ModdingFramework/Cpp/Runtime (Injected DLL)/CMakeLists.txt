project(ModdingFramework.Runtime)

add_library(${PROJECT_NAME} SHARED ModdingFrameworkRuntime.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Injected_DLL Logging StringFormatting)
