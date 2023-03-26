project(ModdingFramework.Runtime)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE ModdingFramework.Types UserInterface Logging Serialization Serialization.Lib)

# Find a way around this disgusting hack
find_path(SIMPLEINI_INCLUDE_DIRS "SimpleIni.h")
target_include_directories(${PROJECT_NAME} INTERFACE include ${SIMPLEINI_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_SOURCE_DIR}/Libraries/Cpp/Serialization/include")

add_library(${PROJECT_NAME}.Lib STATIC ModdingFrameworkRuntimeLib.cpp)
target_link_libraries(${PROJECT_NAME}.Lib PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}.Lib PRIVATE include ${SIMPLEINI_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME}.Lib PRIVATE "${CMAKE_SOURCE_DIR}/Libraries/Cpp/Serialization/include")
