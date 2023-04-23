#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"
#include "engine/resources/textures/Texture.h"
#include "engine/rendering/storage/RenderBuffer.h"

class FrameBuffer {
public:
    FrameBuffer();
    ~FrameBuffer();

    void AttachTexture2D(Texture& texture, GLenum attachment, GLenum textureTarget, GLint level = 0);
    void AttachTexture2D(unsigned int texture, GLenum attachment, GLenum textureTarget, GLint level = 0);

    void AttachRenderBuffer(RenderBuffer& render_buffer, GLenum attachment);

    void Bind();
    void Unbind();

private:
    GLuint m_buffer;
};
