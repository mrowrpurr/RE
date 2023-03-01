project(DLL_Injector.UI VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} DLL_Injector_UI.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ButtonsApp DLLInjection)
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

# TODO : move MultiByte to CMakePresets for this repo
target_compile_definitions(${PROJECT_NAME} PRIVATE MBCS _MBCS _CRT_SECURE_NO_WARNINGS)
