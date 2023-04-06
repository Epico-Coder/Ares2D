#include "Renderer.h"

#include <iostream>
#include <algorithm>

Renderer::Renderer()
{
	// Remains the same
	m_vbl.Push<GLfloat>(2);
	m_vbl.Push<GLfloat>(4);
	m_vbl.Push<GLfloat>(2);
	m_vbl.Push<GLfloat>(1);

	m_vao.AddBuffer(m_vbo, m_vbl);
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

template<>
void Renderer::AddGeometry<Triangle>(Geometry* geometry, const char* id)
{
	if (!m_indices.empty())
	{
		for (int i = 0; i < geometry->m_indices.size(); i++)
		{
			geometry->m_indices[i] += *std::max_element(m_indices.begin(), m_indices.end()) + 1;
		}
	}

	m_Geometries.push_back(geometry);

	m_vertices.insert(m_vertices.end(), geometry->m_vertices.begin(), geometry->m_vertices.end());
	m_indices.insert(m_indices.end(), geometry->m_indices.begin(), geometry->m_indices.end());

	m_vbo.Update(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));

	m_triangles_no += 1;
}

template<>
void Renderer::AddGeometry<Rect>(Geometry* geometry, const char* id)
{
	if (!m_indices.empty())
	{
		for (int i = 0; i < geometry->m_indices.size(); i++)
		{
			geometry->m_indices[i] += *std::max_element(m_indices.begin(), m_indices.end()) + 1;
		}
	}

	m_Geometries.push_back(geometry);

	m_vertices.insert(m_vertices.end(), geometry->m_vertices.begin(), geometry->m_vertices.end());
	m_indices.insert(m_indices.end(), geometry->m_indices.begin(), geometry->m_indices.end());

	m_vbo.Update(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));

	m_rect_no += 1;
}

void Renderer::Update()
{
	m_vertices.clear();
	m_indices.clear();

	for (Geometry* geometry : m_Geometries)
	{
		m_vertices.insert(m_vertices.end(), geometry->m_vertices.begin(), geometry->m_vertices.end());
		m_indices.insert(m_indices.end(), geometry->m_indices.begin(), geometry->m_indices.end());
	}

	m_vbo.Update(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));
	m_vbo.Bind();
}

void Renderer::Draw()
{
	// Temporary buffer, killed out of scope
	// -> make member buffer
	IndexBuffer temp_ibo = IndexBuffer(m_indices.data(), unsigned int(m_indices.size()), 0);
	
	m_vao.Bind();
	glDrawElements(GL_TRIANGLES, temp_ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
}

Renderer::~Renderer()
{
}
