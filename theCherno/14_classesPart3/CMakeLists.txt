cmake_minimum_required(VERSION 3.0.0)
project(classes_part_three VERSION 0.1.0)

include(CTest)

enable_testing()

add_executable(classes_part_three
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
    src/Shader.h
    src/Shader.cpp    
)

target_link_libraries(classes_part_three glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
