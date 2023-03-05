project(DLL_Injector_UI VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} DLL_Injector_UI.cpp app.rc)
target_link_libraries(${PROJECT_NAME} PRIVATE DLL_Injector UserInterface)
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
