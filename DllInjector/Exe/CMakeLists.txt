project(DLL_Injector VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} DLL_Injector.cpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE MBCS _MBCS _CRT_SECURE_NO_WARNINGS)

# Misc:
# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS " /MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" ")
# ^--- if/when we need this!