cmake_minimum_required(VERSION 3.21)

project(Specs.Project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# target_link_libraries(main PRIVATE fmt::fmt)
find_package(fmt CONFIG REQUIRED)

add_subdirectory(Specs)
add_subdirectory(Examples)
