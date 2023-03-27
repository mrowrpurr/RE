project(UserInterface)

find_package(unofficial-nana CONFIG REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE unofficial::nana::nana)

add_library(${PROJECT_NAME}.Lib STATIC UserInterfaceSharedLib.cpp)
target_include_directories(${PROJECT_NAME}.Lib INTERFACE include)
target_link_libraries(${PROJECT_NAME}.Lib PRIVATE unofficial::nana::nana UserInterface)
