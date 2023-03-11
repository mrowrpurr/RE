project(CodeInjection)

find_package(xbyak CONFIG REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE xbyak::xbyak StatefulApp Memory StringFormatting Logging)
