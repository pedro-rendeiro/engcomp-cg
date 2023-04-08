cmake_minimum_required(VERSION 3.0.0)
project(modern_opengl VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(modern_opengl
    src/main.cpp
    src/glad.h
    src/glad.c
)

target_link_libraries(modern_opengl glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
