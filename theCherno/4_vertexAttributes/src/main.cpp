/*
Concepts:
    Vertex buffer = piece of memory on the GPU to store some data
    Shader = code that runs on the GPU and normally access vertex buffers
    Vertex:
        it is NOT a position
        it is a structure with many attributes, one of those beeing a position

Problem:
    How would the shader know how the data is structured? It's just a bunch of bytes.

Solution:
    We have to tell him.
    The process of doing this is called vertex layout.
    And we do this by using the 'glVertexAttribPointer()' function.

Warning:
    Before calling this funcion, be sure that the desired buffer is currently bound.
*/


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

    // Enables a vertex attribute
    glEnableVertexAttribArray(0);  // (attr index)
    
    // Defines the layout for a given attribute
    // (attr index, #elements, type, make_gpu_normalize, how many bytes to the next vertex, how many bytes to the next attr)
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (const void*) 0);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        
        /*
            Draw from a vertex buffer
            Note that we haven't provided the shader yet
            But some manufacturers will used a default shader
            So it may work, as well as it may not
            It is completely manufacturer dependant
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
