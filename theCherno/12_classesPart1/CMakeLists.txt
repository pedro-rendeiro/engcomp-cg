cmake_minimum_required(VERSION 3.0.0)
project(classes_part_one VERSION 0.1.0)

include(CTest)

enable_testing()

add_executable(classes_part_one
    src/Main.cpp
    src/glad.h
    src/glad.c
    src/Renderer.h
    src/Renderer.cpp
    src/VertexBuffer.h
    src/VertexBuffer.cpp
    src/IndexBuffer.h
    src/IndexBuffer.cpp
)

target_link_libraries(classes_part_one glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
