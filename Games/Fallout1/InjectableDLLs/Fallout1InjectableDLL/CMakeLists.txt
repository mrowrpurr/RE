project(Fallout1InjectableDLL)

add_library(${PROJECT_NAME} SHARED Fallout1InjectableDLL.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE Injected_DLL Memory Assembly CodeInjection UserInterface Logging)
