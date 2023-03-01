cmake_minimum_required(VERSION 3.2)

project(ReverseEngineeringPlayground VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(DllInjector)
add_subdirectory(Fallout1)
add_subdirectory(VampireTMB)

find_package(unofficial-nana CONFIG REQUIRED)
add_executable(PlayingWithUI PlayingWithUI.cpp)
target_link_libraries(PlayingWithUI PRIVATE unofficial::nana::nana)
