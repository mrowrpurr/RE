project(ModdingFramework)

add_executable(${PROJECT_NAME} ModdingFramework.cpp ModdingFramework.rc)
target_link_libraries(${PROJECT_NAME} PRIVATE DLL_Injector Serialization Logging)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "modding_framework")
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

if(DEFINED ENV{FALLOUT1_PATH})
    message(STATUS "FALLOUT1_PATH: $ENV{FALLOUT1_PATH}")

    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "$ENV{FALLOUT1_PATH}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
        VERBATIM
    )

    string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type)
    if(build_type STREQUAL debug)
        add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${PROJECT_NAME}>" "$ENV{FALLOUT1_PATH}/$<TARGET_PDB_FILE_NAME:${PROJECT_NAME}>"
            VERBATIM
        )
    endif()
else()
    message(STATUS "FALLOUT1_PATH not set")
endif()