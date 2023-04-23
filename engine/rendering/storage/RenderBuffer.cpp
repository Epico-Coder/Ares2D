#include "RenderBuffer.h"

RenderBuffer::RenderBuffer()
{
    glGenRenderbuffers(1, &m_buffer);
}

RenderBuffer::~RenderBuffer()
{
}

void RenderBuffer::Bind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_buffer);
}

void RenderBuffer::Unbind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBuffer::storage(GLenum format, GLsizei width, GLsizei height)
{
    glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
}

GLuint RenderBuffer::getId() const
{
    return m_buffer;
}
