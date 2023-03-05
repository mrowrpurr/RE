project(LogFormatAndUI)

add_executable(${PROJECT_NAME} LogFormatAndUI.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Logging StringFormatting UserInterface)
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
