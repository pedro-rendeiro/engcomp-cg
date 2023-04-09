cmake_minimum_required(VERSION 3.0.0)
project(classes_part_two VERSION 0.1.0)

include(CTest)

enable_testing()

add_executable(classes_part_two
    src/Main.cpp
    src/glad.h
    src/glad.c
    src/Renderer.h
    src/Renderer.cpp
    src/VertexBuffer.h
    src/VertexBuffer.cpp
    src/IndexBuffer.h
    src/IndexBuffer.cpp
    src/VertexArray.h
    src/VertexArray.cpp
    src/VertexBufferLayout.h
)

target_link_libraries(classes_part_two glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
