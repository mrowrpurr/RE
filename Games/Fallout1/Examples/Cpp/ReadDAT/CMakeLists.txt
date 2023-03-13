project(Fallout1.ReadDAT)

find_package(ZLIB REQUIRED)

set(FALLTERGEIST_PATH "$ENV{FALLTERGEIST_PATH}")

message(STATUS "Falltergeist path: ${FALLTERGEIST_PATH}")

add_subdirectory("${FALLTERGEIST_PATH}" build SYSTEM)

add_executable(${PROJECT_NAME} Fallout1ReadDAT.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE falltergeist)
