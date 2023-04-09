cmake_minimum_required(VERSION 3.0.0)
project(textures VERSION 0.1.0)

include(CTest)

enable_testing()

add_executable(textures
    src/Main.cpp
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
    src/vendor/glad.h
    src/vendor/glad.c
    src/vendor/stb_image.h
    src/vendor/stb_image.cpp
    )
    
    target_link_libraries(textures glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
