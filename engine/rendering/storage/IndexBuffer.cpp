#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count, bool dynamic)
{
    m_count = count;
    glGenBuffers(1, &m_buffer);
    Bind();
    if (dynamic)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
    else
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_buffer);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Update(const void* data, unsigned int count)
{
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(GLuint), data);
}

unsigned int IndexBuffer::GetCount() const
{
    return m_count;
}
