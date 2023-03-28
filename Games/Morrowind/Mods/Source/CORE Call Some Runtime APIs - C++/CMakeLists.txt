project(Morrowind.CORECallSomeRuntimeAPIs.Cpp)

add_library(${PROJECT_NAME} SHARED CORECallSomeRuntimeAPIsCpp.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ModdingFramework Logging StringFormatting)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "CORECallSomeRuntimeAPIs")

# TODO - make a Function for mods to use to copy themselves to the output folder for their game
set(OUTPUT_FOLDER "${CMAKE_SOURCE_DIR}/Games/Morrowind/Mods/Output/CORE Call Some Runtime APIs - C++/Modding/Mods")

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
