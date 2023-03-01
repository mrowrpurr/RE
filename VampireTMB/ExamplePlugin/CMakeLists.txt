project(VampireTheMasquerade.ExamplePlugin)

add_library(${PROJECT_NAME} SHARED vampPlugin.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE DllInjector)

# target_link_libraries(${PROJECT_NAME} PRIVATE VampLib)
target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE _UNICODE MBCS _MBCS _CRT_SECURE_NO_WARNINGS)
