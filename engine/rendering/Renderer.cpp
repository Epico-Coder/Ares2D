#include "Renderer.h"

Renderer::Renderer()
{
	// Remains the same
	m_vbl.Push<GLfloat>(2);
	m_vbl.Push<GLfloat>(4);
	m_vbl.Push<GLfloat>(2);
	m_vbl.Push<GLfloat>(1);
}

void Renderer::DrawTestTriangle(float x, float y, float size) const
{
	glBegin(GL_TRIANGLES);
	glVertex2f(x - size, y);
	glVertex2f(x + size, y);
	glVertex2f(x,        y + (size * 2));
	glEnd();
}

void Renderer::AddTriangle(const char* id, Triangle& triangle)
{
	m_Entities.push_back(EntityStruct{ id, triangle.getPosition(), triangle.getIndices() });
}

void Renderer::UpdateTriangle(const char* id, Triangle& triangle)
{
	for (int i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i].m_id == id)
		{
			m_Entities[i].m_positionVec = triangle.getPosition();
			m_Entities[i].m_indexVec = triangle.getIndices();
		}
	}
}

void Renderer::Draw()
{
	m_positions.clear();
	m_indices.clear();

	for (EntityStruct entity : m_Entities)
	{
		m_positions.insert(m_positions.end(), entity.m_positionVec.begin(), entity.m_positionVec.end());
		m_indices.insert(m_indices.end(), entity.m_indexVec.begin(), entity.m_indexVec.end());
	}

	// Temporary buffers, killed out of scope
	VertexBuffer temp_vbo(m_positions.data(), m_positions.size() * sizeof(float));
	m_vao.AddBuffer(temp_vbo, m_vbl);
	IndexBuffer temp_ibo(m_indices.data(), m_indices.size());

	m_vao.Bind();
	glDrawElements(GL_TRIANGLES, temp_ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
}

Renderer::~Renderer()
{
}