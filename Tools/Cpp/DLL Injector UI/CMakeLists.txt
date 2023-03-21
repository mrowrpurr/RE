project(DLL_Injector_UI VERSION 0.1.0 LANGUAGES CXX)

find_path(SIMPLEINI_INCLUDE_DIRS "SimpleIni.h")

add_executable(${PROJECT_NAME} DLL_Injector_UI.cpp app.rc)
target_link_libraries(${PROJECT_NAME} PRIVATE DLL_Injector UserInterface StringFormatting Logging)
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
target_include_directories(${PROJECT_NAME} PRIVATE ${SIMPLEINI_INCLUDE_DIRS})
