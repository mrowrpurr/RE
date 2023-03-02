project(Fallout1.ExamplePlugin)

add_library(${PROJECT_NAME} SHARED fallout1Plugin.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE FalloutLib DLLInjection ButtonsApp)

# Move to CMake Presets!
target_compile_definitions(${PROJECT_NAME} PRIVATE MBCS _MBCS _CRT_SECURE_NO_WARNINGS)
