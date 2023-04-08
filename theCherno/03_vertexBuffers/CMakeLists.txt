cmake_minimum_required(VERSION 3.0.0)
project(vertex_buffers VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(vertex_buffers
    src/main.cpp
    src/glad.h
    src/glad.c
)

target_link_libraries(vertex_buffers glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
