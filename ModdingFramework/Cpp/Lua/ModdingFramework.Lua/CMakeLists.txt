project(ModdingFramework.Lua)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE ModdingFramework)

# Include the Lua stuff!
# target_link_libraries()
