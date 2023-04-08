cmake_minimum_required(VERSION 3.0.0)
project(breakout VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(breakout
    src/main.cpp
    src/glad.h
    src/glad.c
    src/shader.h
    src/shader.cpp
    src/texture.h
    src/texture.cpp
    src/game.h
    src/game.cpp
    src/resource_manager.h
    src/resource_manager.cpp
)

target_link_libraries(breakout glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
