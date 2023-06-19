#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
{
	m_stride = 0;
}

const std::vector<VertexBufferElement> VertexBufferLayout::GetElements() const&
{
	return m_elements;
}

unsigned int VertexBufferLayout::GetStride() const
{
	return m_stride;
}


template<typename T>
void VertexBufferLayout::Push(unsigned int count)
{}

template<>
void VertexBufferLayout::Push<GLfloat>(unsigned int count)
{
	VertexBufferElement vbe{ GL_FLOAT, count, sizeof(GLfloat), GL_FALSE };
	m_elements.push_back(vbe);
	m_stride += count * vbe.typeSize;
}

template<>
void VertexBufferLayout::Push<GLuint>(unsigned int count)
{
	VertexBufferElement vbe{ GL_UNSIGNED_INT, count, sizeof(GLuint), GL_FALSE };
	m_elements.push_back(vbe);
	m_stride += count * vbe.typeSize;
}

template<>
void VertexBufferLayout::Push<GLubyte>(unsigned int count)
{
	VertexBufferElement vbe{ GL_UNSIGNED_BYTE, count, sizeof(GLubyte), GL_TRUE };
	m_elements.push_back(vbe);
	m_stride += count * vbe.typeSize;
}

template<>
void VertexBufferLayout::Push<glm::vec4>(unsigned int count)
{
	VertexBufferElement vbe{ GL_UNSIGNED_BYTE, count, sizeof(glm::vec4), GL_FALSE };
	m_elements.push_back(vbe);
	m_stride += count * vbe.typeSize;
}
