#include "VertexBuffer.h"

#include <iostream>
#include <memory>

VertexBuffer::VertexBuffer(const void* data, size_t size)
{
    glCreateBuffers(1, &m_buffer);
    glGenBuffers(1, &m_buffer);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::VertexBuffer()
{
    glCreateBuffers(1, &m_buffer);
    glGenBuffers(1, &m_buffer);
    Bind();
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_buffer);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void VertexBuffer::SetSize(unsigned int max_size)
{
    glBufferData(GL_ARRAY_BUFFER, max_size, nullptr, GL_DYNAMIC_DRAW);
}

void VertexBuffer::Update(const void* data, unsigned int size)
{
    glNamedBufferSubData(m_buffer, 0, size, data);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}
