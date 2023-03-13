project(Assembly)

find_package(xbyak CONFIG REQUIRED)
find_package(zydis CONFIG REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE xbyak::xbyak Zydis::Zydis Logging StringFormatting)
