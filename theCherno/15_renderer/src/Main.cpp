#include "glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"

int main()
{
    if(!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    // Shoud not call gladInit() before this
    glfwMakeContextCurrent(window);

    {

        float positions[] =
        {
            -0.5f,  -0.5f,  // 0
            0.5f,  -0.5f,  // 1
            0.5f,   0.5f,  // 2
            -0.5f,   0.5f   // 3
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        // Initializing glad
        gladLoadGL();

        // Instantiates and shapes a VB layout object
        VertexBufferLayout layout;
        layout.Push<float>(2);
        
        // Instantiates a VB object
        VertexBuffer vb(positions, 8 * sizeof(float));
        
        // Instantiates a VA object and links it to a layout and a bufer
        VertexArray va;
        va.AddBuffer(vb, layout);

        // Instantiates an IB object
        IndexBuffer ib(indices, 6);

        // Instantiates a Shader object
        Shader shader("../res/shaders/basic.shader");
        shader.Bind();
        shader.SetUniform4v("u_Color", 0.4, 0.0, 0.4, 1.0);

        // Instantiates a Renderer object
        Renderer renderer;

        // Minimum number of updates before updating screen
        glfwSwapInterval(1);
        float g = 0.0f;
        float increment = 0.05f;

        // Unbinding everything for testing purposes
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();
        va.Unbind();


        while(!glfwWindowShouldClose(window))
        {
            renderer.Clear();            
            renderer.Draw(va, ib, shader);
            
            if(g >= 1.0f)        increment = -0.05f;
            else if(g <= 0.0f)   increment =  0.05f;

            g += increment;
            
            shader.SetUniform4v("u_Color", 0.4f, g, 0.4f, 1.0f);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;

}
