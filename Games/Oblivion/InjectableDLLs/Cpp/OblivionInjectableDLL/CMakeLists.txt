project(OblivionInjectableDLL)

add_library(${PROJECT_NAME} SHARED OblivionInjectableDLL.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE Injected_DLL Hook UserInterface Logging)
