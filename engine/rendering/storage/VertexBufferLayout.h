#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include <vector>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned int typeSize;
	bool normalized;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count);

	template<>
	void Push<GLfloat>(unsigned int count);

	template<>
	void Push<GLuint>(unsigned int count);

	template<>
	void Push<GLubyte>(unsigned int count);

	const std::vector<VertexBufferElement> GetElements() const&;

	unsigned int GetStride() const;
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
};


