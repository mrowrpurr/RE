project(Fallout1.ExamplePlugin)

add_library(${PROJECT_NAME} SHARED plugin.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE DllInjector)
target_link_libraries(${PROJECT_NAME} PRIVATE FalloutLib)
target_compile_definitions(${PROJECT_NAME} PRIVATE MBCS _MBCS _CRT_SECURE_NO_WARNINGS)
