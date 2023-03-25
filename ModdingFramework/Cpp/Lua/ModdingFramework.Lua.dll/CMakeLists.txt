project(ModdingFramework.Lua.DLL)

add_library(${PROJECT_NAME} SHARED ModdingFrameworkLuaDLL.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ModdingFramework.Lua Logging)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "modding_framework.lua")

set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../Games/Fallout1/Mods/Output/Modding Framework - Lua Support/Modding/Mods")

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${OUTPUT_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
    VERBATIM
)
