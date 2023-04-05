#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "dependancies/glew/include/GL/glew.h"

Shader::Shader()
{

}

Shader::~Shader()
{
    glDeleteProgram(m_buffer);
}

void Shader::AddVertexShader(std::string filepath)
{
    m_vertexShader.append(ParseShader(filepath));
}

void Shader::AddFragmentShader(std::string filepath)
{
    m_fragmentShader.append(ParseShader(filepath));
}

std::string Shader::ParseShader(std::string filepath)
{
    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss;
    while (std::getline(stream, line))
    {
        ss << line << '\n';
    }

    return ss.str();
}


void Shader::Create()
{
    m_buffer = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, m_vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, m_fragmentShader);

    glAttachShader(m_buffer, vs);
    glAttachShader(m_buffer, fs);
    glLinkProgram(m_buffer);
    glValidateProgram(m_buffer);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = &source[0];
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "Shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);

        return 0;
    }

    return id;
}

void Shader::Bind()
{
    glUseProgram(m_buffer);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int v1)
{
    glUniform1i(GetUniformLocation(name), v1);
}

void Shader::SetUniform1f(const std::string& name, float v1)
{
    glUniform1f(GetUniformLocation(name), v1);
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
}

void Shader::SetUniform4i(const std::string& name, int v1, int v2, int v3, int v4)
{
    glUniform4i(GetUniformLocation(name), v1, v2, v3, v4);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    int location = glGetUniformLocation(m_buffer, name.c_str());

    if (location == -1)
        std::cout << "Uniform doesnt exist!" << std::endl;

    m_uniformLocationCache[name] = location;
    return location;
}
