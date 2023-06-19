#include "VertexBuffer.h"

#include <iostream>
#include <memory>
#include <vector>

VertexBuffer::VertexBuffer(const void* data, size_t size)
{
    glCreateBuffers(1, &m_buffer);
    glGenBuffers(1, &m_buffer);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    Unbind();
}
VertexBuffer::VertexBuffer()
{
    glCreateBuffers(1, &m_buffer);
    glGenBuffers(1, &m_buffer);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_buffer);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void VertexBuffer::SetSize(unsigned int max_size)
{
    Bind();
    glBufferData(GL_ARRAY_BUFFER, max_size, nullptr, GL_DYNAMIC_DRAW);
    Unbind();
}

void VertexBuffer::Update(const void* data, unsigned int size, GLintptr offset)
{
    Bind();
    glNamedBufferSubData(m_buffer, offset, size, data);
    Unbind();
}
