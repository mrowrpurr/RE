project(ModdingFramework.DLL)

add_library(${PROJECT_NAME} SHARED ModdingFrameworkDLL.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ModdingFramework.Runtime ModdingFramework.Runtime.Lib Injected_DLL Logging StringFormatting Serialization Serialization.Lib UserInterface UserInterface.Lib)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "modding_framework")

# Find a way around this disgusting hack
find_path(SIMPLEINI_INCLUDE_DIRS "SimpleIni.h")
target_include_directories(${PROJECT_NAME} PRIVATE ${SIMPLEINI_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/Libraries/Cpp/Serialization/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/Libraries/Cpp/UserInterface/include")
find_package(unofficial-nana CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE unofficial::nana::nana)

message(STATUS "Including: ${CMAKE_SOURCE_DIR}/Libraries/Cpp/Serialization/include")

set(
    OUTPUT_FOLDERS
    "${CMAKE_SOURCE_DIR}/Games/Morrowind/Mods/Output/Modding Framework"
    "${CMAKE_SOURCE_DIR}/Games/Fallout1/Mods/Output/Modding Framework"
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
