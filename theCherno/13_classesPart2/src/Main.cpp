#include "glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"


struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    
    while(getline(stream,line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                // set mode to vertex
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                // set mode to fragment 
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

 static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
 {
    unsigned int program = glCreateProgram();   // may use GLuint instead
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs); // bind
    glAttachShader(program, fs); // bind
    glLinkProgram(program);
    glValidateProgram(program);

    // Good practice, but may be a pain in the ass
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
 }

int main()
{
    if(!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    // window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    // Shoud not call gladInit() before this
    glfwMakeContextCurrent(window);


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

    ShaderProgramSource source = ParseShader("../res/shaders/basic.shader");

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    GLint location = glGetUniformLocation(shader, "u_Color");
    glUniform4f(location, 0.4f, 0.0f, 0.4f, 1.0f);

    // Minimum number of updates before updating screen
    glfwSwapInterval(1);
    float g = 0.0f;
    float increment = 0.05f;

    // Unbinding everything
    glUseProgram(0);
    vb.Unbind();
    ib.Unbind();
    va.Unbind();

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Rebind everything (comment to see a black screen)
        glUseProgram(shader);
        va.Bind();
        ib.Bind();

        // NOTE THAT I DON'T NEED TO REBIND THE VERTEX BUFFER:
        // glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        if(g >= 1.0f)        increment = -0.05f;
        else if(g <= 0.0f)   increment =  0.05f;

        g += increment;
        
        glUniform4f(location, 0.4f, g, 0.4f, 1.0f);
        
        // Swap front and back buffers (ping pong?)
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;

}
