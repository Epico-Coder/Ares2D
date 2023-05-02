#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
    glGenFramebuffers(1, &m_buffer);
}

FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::AttachTexture2D(Texture& texture, GLenum attachment, GLenum textureTarget, GLint level)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, textureTarget, texture.GetTextureID(), level);
}

void FrameBuffer::AttachTexture2D(unsigned int texture, GLenum attachment, GLenum textureTarget, GLint level)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, textureTarget, texture, level);
}

void FrameBuffer::AttachRenderBuffer(RenderBuffer& render_buffer, GLenum attachment)
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, render_buffer.getId());
}

void FrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_buffer);
}

void FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
