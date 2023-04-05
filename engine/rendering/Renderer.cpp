#include "Renderer.h"

#include <iostream>

Renderer::Renderer()
{
	// Remains the same
	m_vbl.Push<GLfloat>(2);
	m_vbl.Push<GLfloat>(4);
	m_vbl.Push<GLfloat>(2);
	m_vbl.Push<GLfloat>(1);

	m_vao.Bind();
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
	m_Entities.push_back(EntityStruct{ id, triangle.m_vertices, triangle.m_indices });
}

void Renderer::UpdateTriangle(std::string id, Triangle& triangle)
{
	for (int i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i].m_id == id)
		{
			m_Entities.erase(m_Entities.begin()+i);
			m_Entities.push_back(EntityStruct{ id, triangle.m_vertices, triangle.m_indices });
			break;
		}
	}
}

void Renderer::Update()
{
	m_vertices.clear();
	m_indices.clear();

	for (EntityStruct entity : m_Entities)
	{
		m_vertices.insert(m_vertices.end(), entity.m_vertexVec.begin(), entity.m_vertexVec.end());
		m_indices.insert(m_indices.end(), entity.m_indexVec.begin(), entity.m_indexVec.end());
	}

	m_vbo.Update(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));
	//m_ibo.Update(m_indices.data(), m_indices.size());
	m_vao.AddBuffer(m_vbo, m_vbl);
}

void Renderer::Draw()
{
	// Temporary buffer, killed out of scope
	IndexBuffer temp_ibo = IndexBuffer(m_indices.data(), m_indices.size(), 0);
	
	m_vao.Bind();
	glDrawElements(GL_TRIANGLES, temp_ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
}

Renderer::~Renderer()
{
}
