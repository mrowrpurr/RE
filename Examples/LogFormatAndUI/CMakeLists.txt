project(LogFormatAndUI)

add_executable(${PROJECT_NAME} LogFormatAndUI.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE StringFormat Logging)
