#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "engine/rendering/storage/VertexBuffer.h"
#include "engine/rendering/storage/VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind();
	void Unbind();
public:
	unsigned int m_buffer;
};



