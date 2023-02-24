project(DLL_Injector VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} DLL_Injector.cpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE MBCS _MBCS _CRT_SECURE_NO_WARNINGS)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)