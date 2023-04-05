#pragma once

#include "dependancies/glew/include/GL/glew.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data=nullptr, unsigned int size=36000, bool dynamic=1);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void Update(const void* data, unsigned int size);
private:
	unsigned int m_buffer;
};

