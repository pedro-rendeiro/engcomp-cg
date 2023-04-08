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

    float positions[6] = {
        -0.5f,  0.5f,
        0.0f, -0.5f,
        0.5f,  0.5f
    };

    // Initializing glad
    gladLoadGL();

    // Just testing a modern function
    unsigned int buffer;

    // Generates buffers on the GPU and saves its ID into 'buffer'
    glGenBuffers(1, &buffer);   // (#buffers, address)

    // Sets the current state of OpenGL (because it works as an ISM)
    glBindBuffer(GL_ARRAY_BUFFER, buffer);  // (type, ID)
    
    // Copies data into the buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);  // (type,, size, data, mode)

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        
        /*
            Draw from a vertex buffer
            It's not gonna work, because the previous code is incomplete
        */
        glDrawArrays(GL_TRIANGLES, 0, 3);  // (type, offset, #arrays)
        
        // Swap front and back buffers (ping pong?)
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}
