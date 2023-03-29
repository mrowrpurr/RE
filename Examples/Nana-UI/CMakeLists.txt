project(Nana-UI)

find_package(unofficial-nana CONFIG REQUIRED)

add_executable(${PROJECT_NAME} Nana-UI.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::nana::nana)
