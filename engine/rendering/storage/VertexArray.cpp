#include "VertexArray.h"

#include <iostream>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_buffer);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_buffer);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, int offset)
{
	Bind();
	vb.Bind();
	const std::vector<VertexBufferElement> elements = layout.GetElements();
	unsigned int _offset = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		const VertexBufferElement element = elements[i];
		glEnableVertexAttribArray(i + offset);
		glVertexAttribPointer(i + offset, element.count, element.type, element.normalized, layout.GetStride(), (void*)_offset);
		_offset += element.count * element.typeSize;
	}
}

void VertexArray::AddBufferInstanced(const VertexBuffer& vb, const VertexBufferLayout& layout, int offset)
{
	Bind();
	vb.Bind();

	std::size_t vec4Size = sizeof(glm::vec4);

	for (int i = 0; i < 4; i++) 
	{
		// Enable and setup the attribute pointer
		glEnableVertexAttribArray(i + offset);
		glVertexAttribPointer(i + offset, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(sizeof(glm::vec4) * i));

		// Make this attribute instanced
		glVertexAttribDivisor(i + offset, 1);
	}
}

void VertexArray::Bind()
{
	glBindVertexArray(m_buffer);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
