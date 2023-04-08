## Writing shaders
### Create shaders, compile them and link them into a program
There are several ways to do this:
 - Read from a fila
 - Read from raw binary data
 - Read directly from a string

 We're going with the third option, since it's the easiest one to setup at a first moment (but it it is not ideal).


Below there are two auxiliary functions to help with that process. Note that error handling should be implemented.


 ```c
static unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    return id;
}

 static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program = glCreateProgram();   // may use GLuint instead
    unsigned int vs = glCompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = glCompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs); // bind
    glAttachShader(program, fs); // bind
    glLinkProgram(program);
    glValidateProgram(program);

    // Good practice, but may be a pain in the ass
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
 }
 
 ```

 ### Writing shader
 Using directly a c++ string, it would be something like:

 ```c
 std::string vertexShader = 
     "#version 330 core\n"
     "layout(location=0) in vec4 position;\n"
     "\n"
     "void main(){\n"
     "gl_Position = position;\n"
     "}\n"

 std::string vertexShader = 
     "#version 330 core\n"
     "out vec4 position;\n"
     "\n"
     "void main(){\n"
     "color = vec4(0.0, 1.0, 0.0, 1.0);\n"
     "}\n"

 ```
