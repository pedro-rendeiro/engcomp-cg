#include "vendor/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "vendor/im_gui/imgui.h"
#include "vendor/im_gui/imgui_impl_glfw_gl3.h"


int main()
{
    if(!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    // Shoud not call gladInit() before this
    glfwMakeContextCurrent(window);
    
    // Initializing glad
    gladLoadGL();


    {

        float positions[] =
        {
            000.0f,  000.0f,  0.0f,  0.0f,  // 0
            200.0f,  000.0f,  1.0f,  0.0f,  // 1
            200.0f,  200.0f,  1.0f,  1.0f,  // 2
            000.0f,  200.0f,  0.0f,  1.0f   // 3
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        // Enables blending and defines the math config
        // Technicaly I should do this
        // But in my experience, it makes no difference
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Instantiates and shapes a VB layout object
        VertexBufferLayout layout;
        layout.Push<float>(2);  // position
        layout.Push<float>(2);  // texture coordinates
        
        // Instantiates a VB object
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        
        // Instantiates a VA object and links it to a layout and a bufer
        VertexArray va;
        va.AddBuffer(vb, layout);

        // Instantiates an IB object
        IndexBuffer ib(indices, 6);

        // MVP matrix
        glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);      // Projection matrix
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(16*20, 0, 0));   // View matrix

        // Instantiates a Shader object
        Shader shader("../res/shaders/basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.4, 0.0, 0.4, 1.0);

        // Instantiates a Texture object
        Texture texture("../res/textures/awesomeface.png");
        unsigned int slot = 0;
        texture.Bind(slot);
        shader.SetUniform1i("u_Texture", slot);

        // Instantiates a Renderer object
        Renderer renderer;

        // Setup ImGui
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        // Minimum number of updates before updating screen
        glfwSwapInterval(1);
        float g = 0.0f;
        float increment = 0.05f;
        glm::vec3 translation(0, 9*20, 0);
        // bool show_demo_window = true;
        // bool show_another_window = false;
        // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // Unbinding everything for testing purposes
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();
        va.Unbind();


        while(!glfwWindowShouldClose(window))
        {
            renderer.Clear();
            ImGui_ImplGlfwGL3_NewFrame();
            
            renderer.Draw(va, ib, shader);
            
            if(g >= 1.0f)        increment = -0.05f;
            else if(g <= 0.0f)   increment =  0.05f;
            g += increment;
            
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);  // Model matrix
            glm::mat4 mvp = proj * view * model;

            shader.SetUniformMath4f("u_MVP", mvp);
            shader.SetUniform4f("u_Color", 0.4f, g, 0.4f, 1.0f);

            // Show a simple window.
            {
                // static float f = 0.0f;
                // static int counter = 0;
                // ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
                ImGui::SliderFloat2("Translation", &translation.x, 0.0f, 1280.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
                // ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                // ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
                // ImGui::Checkbox("Another Window", &show_another_window);

                // if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                //     counter++;
                ImGui::SameLine();
                // ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    // Cleanup
    // ImGui_ImplGlfwGL3_Shutdown();
    // ImGui::DestroyContext();
    // glfwTerminate();
    return 0;

}
