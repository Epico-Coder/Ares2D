#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_buffer);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_buffer);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const std::vector<VertexBufferElement> elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		const VertexBufferElement element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (unsigned int*)offset);
		offset += element.count * element.typeSize;
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
