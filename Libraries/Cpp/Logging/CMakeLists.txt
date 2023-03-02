project(Logging)

find_package(spdlog CONFIG REQUIRED)

add_library(Logging INTERFACE)
target_include_directories(Logging INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE spdlog::spdlog_header_only)
