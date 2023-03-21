project(LoadThisDLL1)

add_library(${PROJECT_NAME} SHARED LoadThisDLL1.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Logging)
