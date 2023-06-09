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
    window = glfwCreateWindow(1280, 720, "Computer Graphics - 2D Project", NULL, NULL);
    
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
            -100.0f,  -100.0f,  0.0f,  0.0f,  // 0
             100.0f,  -100.0f,  1.0f,  0.0f,  // 1
             100.0f,   100.0f,  1.0f,  1.0f,  // 2
            -100.0f,   100.0f,  0.0f,  1.0f   // 3
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
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));   // View matrix

        // Instantiates a Shader object
        Shader shader("../res/shaders/basic.shader");
        shader.Bind();

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

        // Matrix transformation
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 mvp   = glm::mat4(1.0f);
        glm::vec3 translationA(640, 360, 0);
        glm::vec3 translationB(100, 100, 0);
        float rotationA =  45.0f;
        float rotationB = -45.0f;
        glm::vec3 scaleA(0.5, 0.5, 0.5);
        glm::vec3 scaleB(2.0, 2.0, 2.0);
        
        // glMultMatrixf(transformationMatrix);

        // Unbinding everything for testing purposes
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();
        va.Unbind();


        while(!glfwWindowShouldClose(window))
        {
            renderer.Clear();
            ImGui_ImplGlfwGL3_NewFrame();
            
            // Draw instance A
            {
                model = glm::translate(glm::mat4(1.0f), translationA);  // Translate
                model = glm::rotate(model, glm::radians(rotationA), glm::vec3(0.0, 0.0, 1.0));
                model = glm::scale(model, scaleA);
                mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMath4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);
            }

            // Draw instance B
            {
                model = glm::translate(glm::mat4(1.0f), translationB);  // Translate
                model = glm::rotate(model, glm::radians(rotationB), glm::vec3(0.0, 0.0, 1.0));
                model = glm::scale(model, scaleB);
                mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMath4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);
            }

            ImGui::Text("Transformations on A");
            ImGui::SliderFloat2("Translation A", &translationA.x, 0.0f, 1280.0f);
            ImGui::SliderFloat("Rotation A", &rotationA, -360.0f, 360.0f);
            ImGui::SliderFloat2("Scaling A", &scaleA.x, 0.0f, 10.0f);

            ImGui::Text("\nTransformations on B");
            ImGui::SliderFloat2("Translation B", &translationB.x, 0.0f, 1280.0f);
            ImGui::SliderFloat("Rotation B", &rotationB, -360.0f, 360.0f);
            ImGui::SliderFloat2("Scaling B", &scaleB.x, 0.0f, 10.0f);

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;

}
