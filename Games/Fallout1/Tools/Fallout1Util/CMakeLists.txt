project(Fallout1.ExamplePlugin)

add_library(${PROJECT_NAME} SHARED Fallout1Util.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE FalloutLib LibRE FormApp Logging StringFormat)
