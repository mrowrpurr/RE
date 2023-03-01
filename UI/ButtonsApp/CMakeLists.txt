project(ButtonsApp.UI VERSION 0.1.0 LANGUAGES CXX)

find_package(unofficial-nana CONFIG REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE unofficial::nana::nana)
