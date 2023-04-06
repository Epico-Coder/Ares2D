#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, size_t size, bool dynamic)
{
    glCreateBuffers(1, &m_buffer);
    glGenBuffers(1, &m_buffer);
    Bind();
    if (dynamic)
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    else
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_buffer);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void VertexBuffer::Update(const void* data, size_t size)
{
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}
