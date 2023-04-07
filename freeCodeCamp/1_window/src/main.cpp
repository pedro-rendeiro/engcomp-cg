#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>

int main(){

    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 800, "My Window", NULL, NULL);

    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    //     std::cout << "Failed to load OpenGL" << std::endl;
    //     glfwTerminate();
    //     return -1;
    // }
    gladLoadGL();
    glViewport(0, 0, 800, 800);

    glClearColor(0.33f, 0.10f, 0.33f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        // glfwSwapBuffers(window);
    }
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}