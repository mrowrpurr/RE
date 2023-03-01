project(Fallout1.ExamplePlugin)

find_package(unofficial-nana CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED fallout1Plugin.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE DllInjector)
target_link_libraries(${PROJECT_NAME} PRIVATE FalloutLib)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::nana::nana)
target_compile_definitions(${PROJECT_NAME} PRIVATE MBCS _MBCS _CRT_SECURE_NO_WARNINGS)