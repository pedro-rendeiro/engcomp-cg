#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath){
    std::ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    
    while(getline(stream,line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos){
                // set mode to vertex
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos){
                // set mode to fragment 
                type = ShaderType::FRAGMENT;
            }
        }else{
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
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

 static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
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

    // unsigned int VAO;
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);

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

    ShaderProgramSource source = ParseShader("../res/shaders/basic.shader");

    // std::cout << "vertexShader:\n" << source.VertexSource << std::endl;
    // std::cout << "fragmentShader:\n" << source.FragmentSource << std::endl;

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);  // (type, offset, #arrays)
        
        // Swap front and back buffers (ping pong?)
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;

}
