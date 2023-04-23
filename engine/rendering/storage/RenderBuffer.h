#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

class RenderBuffer {
public:
    RenderBuffer();
    ~RenderBuffer();

    void Bind();
    void Unbind();
    void storage(GLenum format, GLsizei width, GLsizei height);
    GLuint getId() const;

private:
    GLuint m_buffer;
};