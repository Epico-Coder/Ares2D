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
	glVertex2f(x - size, y             );
	glVertex2f(x + size, y             );
	glVertex2f(x,        y + (size * 2));
	glEnd();
}

void Renderer::AddGeometry(Geometry& geometry, const char* id)
{
	m_Batches.back()->AddGeometry(geometry, id);
}

void Renderer::Clear()
{
	for (int i = 0; i < m_Batches.size(); i++)
	{
		m_Batches[i]->Clear();
	}
}

void Renderer::Update()
{
	if (m_Batches.back()->getIndicesCount() >= m_Batches.back()->getIndicesMaxCount())
	{
		AddBatch(m_batchSize);
	}

	std::cout << "------------------------------------------------------------------" << std::endl;
	std::cout << "Batches: " << m_Batches.size() << std::endl;
	
	for (Batch* batch : m_Batches)
	{
		batch->Update();
		//std::cout << "Geometries: " << batch->getGeometryCount() << std::endl;
		std::cout << "Vetices: " << batch->getVerticesCount() << std::endl;
		std::cout << "Indices: " << batch->getIndicesCount() << std::endl;
	}
	std::cout << "------------------------------------------------------------------" << std::endl;
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
	m_vbl.Push<GLfloat>(1);

	m_vao.AddBuffer(m_vbo, m_vbl);
	m_ibo.Bind();

}

Renderer::Batch::~Batch()
{
}

void Renderer::Batch::AddGeometry(Geometry& geometry, const char* id)
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
	
	//m_Geometries.push_back(geometry);
}

void Renderer::Batch::Clear()
{
	m_vertices.clear();
	m_indices.clear();
}

void Renderer::Batch::Update()
{	
	m_vbo.Update(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));
	m_ibo.Update(m_indices.data(), m_indices.size());
}

void Renderer::Batch::Draw()
{
	m_vao.Bind();

	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}
