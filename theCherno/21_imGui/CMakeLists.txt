cmake_minimum_required(VERSION 3.0.0)
project(im_gui VERSION 0.1.0)

include(CTest)

enable_testing()

add_executable(im_gui
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
    src/vendor/im_gui/imconfig.h
    src/vendor/im_gui/imgui_demo.cpp
    src/vendor/im_gui/imgui_draw.cpp
    src/vendor/im_gui/imgui_impl_glfw_gl3.h
    src/vendor/im_gui/imgui_impl_glfw_gl3.cpp
    src/vendor/im_gui/imgui_internal.h
    src/vendor/im_gui/imgui.cpp
    src/vendor/im_gui/imgui.h
    src/vendor/im_gui/stb_rect_pack.h
    src/vendor/im_gui/stb_textedit.h
    src/vendor/im_gui/stb_truetype.h
)
    
    target_link_libraries(im_gui glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
