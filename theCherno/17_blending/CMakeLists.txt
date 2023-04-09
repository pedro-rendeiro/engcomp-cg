cmake_minimum_required(VERSION 3.0.0)
project(blending VERSION 0.1.0)

include(CTest)

enable_testing()

add_executable(blending
    src/Application.cpp
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
    src/Texture.h
    src/Texture.cpp
    src/vendor/glad.h
    src/vendor/glad.c
    src/vendor/stb_image.h
    src/vendor/stb_image.cpp
)
    
    target_link_libraries(blending glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
