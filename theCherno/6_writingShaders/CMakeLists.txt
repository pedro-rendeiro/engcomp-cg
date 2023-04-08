cmake_minimum_required(VERSION 3.0.0)
project(writing_shaders VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(writing_shaders
    src/main.cpp
    src/glad.h
    src/glad.c
)

target_link_libraries(writing_shaders glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
