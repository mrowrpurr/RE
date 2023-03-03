project(Fallout1InjectableDLL)

add_library(${PROJECT_NAME} SHARED Fallout1InjectableDLL.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE FalloutLib LibRE FormApp Logging StringFormat)
