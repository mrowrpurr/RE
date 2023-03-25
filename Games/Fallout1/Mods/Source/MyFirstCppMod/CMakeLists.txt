project(MyFirstCppMod)

add_library(${PROJECT_NAME} SHARED MyFirstCppMod.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Logging)

set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Output/My First C++ Mod/Modding/Mods")

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${OUTPUT_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
    VERBATIM
)
