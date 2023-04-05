#pragma once

#include "dependancies/glew/include/GL/glew.h"

class IndexBuffer
{
public:
	IndexBuffer(const void* data = nullptr, unsigned int count = 1000, bool dynamic = true);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	void Update(const void* data, unsigned int count);

	unsigned int GetCount() const;
private:
	unsigned int m_buffer;
	unsigned int m_count;
};



