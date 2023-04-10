#include "Renderer.h"

#include <iostream>
#include <algorithm>

Renderer::Renderer(unsigned int batchSize)
{
	m_batchSize = batchSize;
	AddBatch(m_batchSize);
}

Renderer::~Renderer()
{
	for (Batch* batch : m_Batches)
		delete(batch);
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
void Renderer::AddGeometry<Triangle>(Geometry& geometry, const char* id)
{
	m_Batches.back()->AddGeometry<Triangle>(geometry, id);
	m_triangle_no += 1;
}

template<>
void Renderer::AddGeometry<Rect>(Geometry& geometry, const char* id)
{
	m_Batches.back()->AddGeometry<Rect>(geometry, id);
	m_triangle_no += 2;
}

void Renderer::Update()
{
	if (m_Batches.back()->getGeometryCount() >= m_batchSize)
		AddBatch(m_batchSize);
	
	std::cout << "------------------------------------------------------------------" << std::endl;
	std::cout << "Batches: " << m_Batches.size() << std::endl;
	std::cout << "Triangles: " << m_triangle_no << std::endl;
	std::cout << "------------------------------------------------------------------" << std::endl;

	for (int i = 0; i < m_Batches.size(); i++)
	{
		Batch* batch = m_Batches[i];
		batch->Update();
	}
}

void Renderer::Draw()
{
	for (int i = 0; i < m_Batches.size(); i++)
	{
		m_Batches[i]->Draw();
	}
}

void Renderer::AddBatch(unsigned int batchSize)
{
	m_Batches.push_back(new Batch(batchSize));
}

Renderer::Batch::Batch(unsigned int batchSize)
{
	m_BatchSize = batchSize;

	m_vbo.SetSize(batchSize * sizeof(Vertex) * sizeof(GLfloat));
	m_ibo.SetCount(batchSize * 10);

	m_vbl.Push<GLfloat>(2);
	m_vbl.Push<GLfloat>(4);
	m_vbl.Push<GLfloat>(2);
	m_vbl.Push<GLfloat>(1);

	m_vao.AddBuffer(m_vbo, m_vbl);
}

Renderer::Batch::~Batch()
{
}

template<>
void Renderer::Batch::AddGeometry<Triangle>(Geometry& geometry, const char* id)
{
	if (!m_indices.empty())
	{
		for (int i = 0; i < geometry.m_indices.size(); i++)
		{
			geometry.m_indices[i] += *std::max_element(m_indices.begin(), m_indices.end()) + 1;
		}
	}

	m_vertices.insert(m_vertices.end(), geometry.m_vertices.begin(), geometry.m_vertices.end());
	m_indices.insert(m_indices.end(), geometry.m_indices.begin(), geometry.m_indices.end());
	
	m_Geometries.push_back(geometry);
}

template<>
void Renderer::Batch::AddGeometry<Rect>(Geometry& geometry, const char* id)
{
	if (!m_indices.empty())
	{
		for (int i = 0; i < geometry.m_indices.size(); i++)
		{
			geometry.m_indices[i] += *std::max_element(m_indices.begin(), m_indices.end()) + 1;
		}
	}

	m_Geometries.push_back(geometry);
}

void Renderer::Batch::Update()
{
	m_vertices.clear();
	m_indices.clear();

	for (Geometry& geometry : m_Geometries)
	{
		m_vertices.insert(m_vertices.end(), geometry.m_vertices.begin(), geometry.m_vertices.end());
		m_indices.insert(m_indices.end(), geometry.m_indices.begin(), geometry.m_indices.end());
	}

	m_vbo.Update(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));
	m_ibo.Update(m_indices.data(), m_indices.size());
}

void Renderer::Batch::Draw()
{
	m_vao.Bind();
	m_ibo.Bind();

	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}
