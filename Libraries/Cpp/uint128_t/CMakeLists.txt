project(uint128_t)

add_library(${PROJECT_NAME} STATIC uint128_t.cpp uint128_t.h)
target_include_directories(${PROJECT_NAME} PUBLIC .)
