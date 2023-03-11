project(DiabloInjectableDLL)

add_library(${PROJECT_NAME} SHARED DiabloInjectableDLL.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE Injected_DLL CodeInjection Memory UserInterface Logging StringFormatting)
