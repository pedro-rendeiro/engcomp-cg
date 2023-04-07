#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>

int main(int, char**) {
    if(!glfwInit()) return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(!window){
        glfwTerminate();
        return -1;
    }

    // Shoud not call gladInit() before this
    glfwMakeContextCurrent(window);

    /*
        Initializing glad
        Should not call any modern (+1997) OpenGL functions before this
    */
    gladLoadGL();

    // Just testing a modern function
    unsigned a;
    glGenBuffers(1, &a);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        
        // Swap front and back buffers (ping pong?)
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}
