project(Serialization)

find_path(SIMPLEINI_INCLUDE_DIRS "SimpleIni.h")

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_include_directories(${PROJECT_NAME} INTERFACE ${SIMPLEINI_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE StringFormatting)
