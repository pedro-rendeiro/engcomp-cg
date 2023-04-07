cmake_minimum_required(VERSION 3.0.0)
project(cherno_window VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(OpenGL REQUIRED)

add_executable(cherno_window src/main.cpp)

target_link_libraries(cherno_window glfw OpenGL)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
