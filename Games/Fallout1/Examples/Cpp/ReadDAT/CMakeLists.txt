project(Fallout1.ReadDAT)

set(Boost_NO_WARN_NEW_VERSIONS 1)

find_package(ZLIB REQUIRED)

set(DAT_UNPACKER_LIB "$ENV{DAT_UNPACKER_LIB}")
message(STATUS "DAT unpacker path: ${DAT_UNPACKER_LIB}")

add_subdirectory("${DAT_UNPACKER_LIB}" build SYSTEM)

add_executable(${PROJECT_NAME} Fallout1ReadDAT.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE dat-unpacker)
