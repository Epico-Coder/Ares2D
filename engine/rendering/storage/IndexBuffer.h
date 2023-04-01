#pragma once

#include "dependancies/glew/include/GL/glew.h"

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int GetCount() const;
private:
	unsigned int m_buffer;
	unsigned int m_count;
};



