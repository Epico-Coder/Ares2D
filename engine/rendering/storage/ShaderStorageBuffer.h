#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

class ShaderStorageBuffer
{
public:
    ShaderStorageBuffer();
    ShaderStorageBuffer(const void* data, GLsizeiptr size);
    ~ShaderStorageBuffer();

    void Bind() const;
    void BindIndex(unsigned int index=0) const;
    void Unbind() const;
    void UnbindIndex(unsigned int index=0) const;

    void SetSize(unsigned int max_size = 100000);
    void Update(const GLvoid* data, GLsizeiptr size, GLintptr offset);

private:
    GLuint m_buffer;
};

