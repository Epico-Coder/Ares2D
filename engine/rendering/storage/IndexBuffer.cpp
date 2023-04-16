#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
{
    m_count = count;
    glGenBuffers(1, &m_buffer);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &m_buffer);
    Bind();
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

void IndexBuffer::SetCount(unsigned int max_count)
{
    m_count = max_count;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_count * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
}

void IndexBuffer::Update(const void* data, unsigned int count, unsigned int offset)
{ 
    glNamedBufferSubData(m_buffer, offset * sizeof(GLuint), count * sizeof(GLuint), data);
}

unsigned int IndexBuffer::GetCount() const
{
    return m_count;
}
