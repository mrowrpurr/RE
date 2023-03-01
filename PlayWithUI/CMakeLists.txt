project(PlayWithUI VERSION 1.0.0 LANGUAGES CXX)

find_package(unofficial-nana CONFIG REQUIRED)

add_executable(${PROJECT_NAME} playWithUI.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::nana::nana)
