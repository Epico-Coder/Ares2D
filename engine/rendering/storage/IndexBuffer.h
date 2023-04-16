#pragma once

#include "dependancies/glew/include/GL/glew.h"

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int count);
	IndexBuffer();
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetCount(unsigned int max_count = 1024);
	void Update(const void* data, unsigned int count, unsigned int offset = 0);

	unsigned int GetCount() const;
private:
	unsigned int m_buffer;
	unsigned int m_count;
};



