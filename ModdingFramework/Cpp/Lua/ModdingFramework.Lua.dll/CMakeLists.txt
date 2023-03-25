project(ModdingFramework.Lua.DLL)

add_library(${PROJECT_NAME} SHARED ModdingFrameworkLuaDLL.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ModdingFramework ModdingFramework.Lua Logging)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "modding_framework.lua")

set(
    OUTPUT_FOLDERS
    "${CMAKE_SOURCE_DIR}/Games/Morrowind/Mods/Output/Modding Framework - Lua Support/Modding/Mods"
    "${CMAKE_SOURCE_DIR}/Games/Fallout1/Mods/Output/Modding Framework - Lua Support/Modding/Mods"
)

foreach(OUTPUT_FOLDER ${OUTPUT_FOLDERS})
    message(STATUS "Copying ${PROJECT_NAME} to ${OUTPUT_FOLDER}")
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${OUTPUT_FOLDER}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
        VERBATIM
    )

    string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type)
    if(build_type STREQUAL debug)
        add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${PROJECT_NAME}>" "${OUTPUT_FOLDER}/$<TARGET_PDB_FILE_NAME:${PROJECT_NAME}>"
            VERBATIM
        )
    endif()
endforeach()

