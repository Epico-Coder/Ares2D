#pragma once

#include "dependancies/glew/include/GL/glew.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, size_t size);
	VertexBuffer();
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetSize(unsigned int max_size = 36864);
	void Update(const void* data, unsigned int size);
private:
	unsigned int m_buffer;
};

