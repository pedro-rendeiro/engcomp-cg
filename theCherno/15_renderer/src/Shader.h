#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    const std::string& m_FilePath;
    unsigned int m_RendererID;
    // Location cache, so we don't have to call glGetUniformLocation() everytime
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& filePath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4v(const std::string& name, float v0, float v1, float v2, float v3);
private:
    int GetUniformLocation(const std::string& name);
    ShaderProgramSource ParseShader(const std::string& filepath);
    static unsigned int CompileShader(unsigned int type, const std::string& source);
    static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};