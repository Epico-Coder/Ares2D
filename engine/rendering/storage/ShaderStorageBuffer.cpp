#include "ShaderStorageBuffer.h"

#include "ShaderStorageBuffer.h"

ShaderStorageBuffer::ShaderStorageBuffer()
{
    glGenBuffers(1, &m_buffer);
}

ShaderStorageBuffer::ShaderStorageBuffer(const void* data, GLsizeiptr size)
{
    glGenBuffers(1, &m_buffer);
    Bind();
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
    Unbind();
}

ShaderStorageBuffer::~ShaderStorageBuffer()
{
    glDeleteBuffers(1, &m_buffer);
}

void ShaderStorageBuffer::Bind() const
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_buffer);
}

void ShaderStorageBuffer::BindIndex(unsigned int index) const
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, m_buffer);
}

void ShaderStorageBuffer::Unbind() const
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ShaderStorageBuffer::UnbindIndex(unsigned int index) const
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, 0);
}

void ShaderStorageBuffer::Update(const GLvoid* data, GLsizeiptr size, GLintptr offset)
{
    Bind();
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
    Unbind();
}

void ShaderStorageBuffer::SetSize(unsigned int size)
{
    Bind();
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    Unbind();
}
