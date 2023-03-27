project(Serialization)

find_path(SIMPLEINI_INCLUDE_DIRS "SimpleIni.h")

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include ${SIMPLEINI_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE StringFormatting)

add_library(${PROJECT_NAME}.Lib STATIC SerializationSharedLib.cpp)
target_include_directories(${PROJECT_NAME}.Lib PRIVATE include ${SIMPLEINI_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}.Lib PRIVATE Serialization StringFormatting)
