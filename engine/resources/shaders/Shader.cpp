#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "dependancies/glew/include/GL/glew.h"

ShaderHandler::ShaderHandler()
{
}

ShaderHandler::~ShaderHandler()
{
}

void ShaderHandler::AddShader(const std::string& vert_file_path, const std::string& frag_file_path, int shaderID)
{
    m_Shaders[shaderID] = new Shader(vert_file_path, frag_file_path);
}

void ShaderHandler::RemoveShader(int shaderID)
{
    auto iter =  m_Shaders.find(shaderID);
    if (iter == m_Shaders.end()) {
        std::cout << "Audio with ID " << shaderID << " does not exist" << std::endl;
    }
    else
    {
        m_Shaders.erase(iter);
    }
}

void ShaderHandler::BindShader(int shaderID)
{
    auto iter = m_Shaders.find(shaderID);
    if (iter == m_Shaders.end()) {
        std::cout << "Audio with ID " << shaderID << " does not exist" << std::endl;
    }
    else
    {
        iter->second->Bind();
    }
}

void ShaderHandler::CreateUniform1i(int shaderID, const std::string& name)
{

}

void ShaderHandler::CreateUniform1iv(int shaderID, const std::string& name)
{

}

void ShaderHandler::CreateUniform1f(int shaderID, const std::string& name)
{

}

void ShaderHandler::CreateUniform3f(int shaderID, const std::string& name)
{

}

void ShaderHandler::CreateUniform4i(int shaderID, const std::string& name)
{

}

void ShaderHandler::CreateUniform4f(int shaderID, const std::string& name)
{

}

void ShaderHandler::CreateUniformMat4f(int shaderID, const std::string& name)
{

}

void ShaderHandler::SetUniform1i(int shaderID, const std::string& name, int v1)
{
    auto shader = m_Shaders.find(shaderID);
    if (shader != m_Shaders.end()) {
        shader->second->SetUniform1i(name, v1);
    }
}

void ShaderHandler::SetUniform1iv(int shaderID, const std::string& name, unsigned int count, int v1[])
{
    auto shader = m_Shaders.find(shaderID);
    if (shader != m_Shaders.end()) {
        shader->second->SetUniform1iv(name, count, v1);
    }
}

void ShaderHandler::SetUniform1f(int shaderID, const std::string& name, float v1)
{
    auto shader = m_Shaders.find(shaderID);
    if (shader != m_Shaders.end()) {
        shader->second->SetUniform1f(name, v1);
    }
}

void ShaderHandler::SetUniform2fv(int shaderID, const std::string& name, const glm::vec2& vec)
{
    auto shader = m_Shaders.find(shaderID);
    if (shader != m_Shaders.end()) {
        shader->second->SetUniform2fv(name, vec);
    }
}

void ShaderHandler::SetUniform3f(int shaderID, const std::string& name, float v1, float v2, float v3)
{
    auto shader = m_Shaders.find(shaderID);
    if (shader != m_Shaders.end()) {
        shader->second->SetUniform3f(name, v1, v2, v3);
    }
}

void ShaderHandler::SetUniform4i(int shaderID, const std::string& name, int v1, int v2, int v3, int v4)
{
    auto shader = m_Shaders.find(shaderID);
    if (shader != m_Shaders.end()) {
        shader->second->SetUniform4i(name, v1, v2, v3, v4);
    }
}

void ShaderHandler::SetUniform4f(int shaderID, const std::string& name, float v1, float v2, float v3, float v4)
{
    auto shader = m_Shaders.find(shaderID);
    if (shader != m_Shaders.end()) {
        shader->second->SetUniform4f(name, v1, v2, v3, v4);
    }
}

void ShaderHandler::SetUniform4fv(int shaderID, const std::string& name, const glm::vec4& vec)
{
    auto shader = m_Shaders.find(shaderID);
    if (shader != m_Shaders.end()) {
        shader->second->SetUniform4fv(name, vec);
    }
}

void ShaderHandler::SetUniformMat4f(int shaderID, const std::string& name, const glm::mat4& matrix)
{
    auto shader = m_Shaders.find(shaderID);
    if (shader != m_Shaders.end()) {
        shader->second->SetUniformMat4f(name, matrix);
    }
}

void ShaderHandler::PrintShader(int shaderID)
{
    auto shader = m_Shaders.find(shaderID);
    if (shader != m_Shaders.end()) {
        shader->second->Print();
    }
}

Shader::Shader()
{
}

Shader::Shader(const std::string& vert_file_path, const std::string& frag_file_path)
{
    AddVertexShader(vert_file_path);
    AddFragmentShader(frag_file_path);
    Create();
}

Shader::~Shader()
{
    glDeleteProgram(m_buffer);
}

void Shader::AddVertexShader(const std::string& filepath)
{
    m_vertexShader.append(ParseShader(filepath));
}

void Shader::AddFragmentShader(const std::string& filepath)
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

void Shader::SetUniform1iv(const std::string& name, unsigned int count, int v1[])
{
    glUniform1iv(GetUniformLocation(name), count, v1);
}

void Shader::SetUniform1f(const std::string& name, float v1)
{
    glUniform1f(GetUniformLocation(name), v1);
}

void Shader::SetUniform1fv(const std::string& name, unsigned int count, float v1[])
{
    glUniform1fv(GetUniformLocation(name), count, v1);
}

void Shader::SetUniform2fv(const std::string& name, const glm::vec2& vec)
{
    GLfloat data[2] = { vec.x, vec.y };
    glUniform2fv(GetUniformLocation(name), 1, data);
}

void Shader::SetUniform3f(const std::string& name, float v1, float v2, float v3)
{
    glUniform3f(GetUniformLocation(name), v1, v2, v3);
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
}

void Shader::SetUniform4fv(const std::string& name, const glm::vec4& vec)
{
    glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(vec));
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

void Shader::Print()
{
    GLuint feedbackBufferId;
    glGenBuffers(1, &feedbackBufferId);

    // Bind the feedback buffer
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, feedbackBufferId);
    glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float), nullptr, GL_STATIC_READ);

    // Start a transform feedback operation
    glBeginTransformFeedback(GL_POINTS);

    // Draw one point to trigger the shader program and write data to the feedback buffer
    glDrawArrays(GL_POINTS, 0, 1);

    // End the transform feedback operation
    glEndTransformFeedback();

    // Map the feedback buffer and retrieve the feedback data
    float value;
    void* feedbackData = glMapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, GL_READ_ONLY);
    memcpy(&value, feedbackData, sizeof(float));
    glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER);

    // Print the feedback value
    printf("Feedback value: %f\n", value);

    // Clean up resources
    glDeleteBuffers(1, &feedbackBufferId);

}