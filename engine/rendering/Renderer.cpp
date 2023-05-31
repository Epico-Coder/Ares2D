#include <iostream>
#include <algorithm>

#include "Renderer.h"

namespace Ares2D
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
		for (Batch* batch : m_Batches)
			delete(batch);
	}

	/*-------------------------- Public Functions --------------------------*/

	Renderer& Renderer::Instance()
	{
		static Renderer instance;
		return instance;
	}

	void Renderer::Init(unsigned int batchSize)
	{
		Instance().i_Init(batchSize);
	}

	void Renderer::DrawTestTriangle(float x, float y, float size)
	{
		Instance().i_DrawTestTriangle(x, y, size);
	}

	void Renderer::AddRenderable(Renderable renderable, const char* id)
	{
		Instance().i_AddRenderable(renderable, id);
	}

	void Renderer::Clear()
	{
		Instance().i_Clear();
	}

	void Renderer::Update(bool show_info)
	{
		Instance().i_Update(show_info);
	}

	void Renderer::Draw(bool show_info)
	{
		Update(show_info);
		Instance().i_Draw(show_info);
	}

	/*-------------------------- Internal Functions --------------------------*/

	void Renderer::i_Init(unsigned int batchSize)
	{
		m_batchSize = batchSize;
		AddBatch(m_batchSize);
	}

	void Renderer::i_DrawTestTriangle(float x, float y, float size)
	{
		glBegin(GL_TRIANGLES);
		glVertex2f(x - size, y);
		glVertex2f(x + size, y);
		glVertex2f(x, y + (size * 2));
		glEnd();
	}

	void Renderer::i_AddRenderable(Renderable& renderable, const char* id)
	{
		m_Batches.back()->AddRenderable(renderable, id);
	}

	void Renderer::i_Clear()
	{
		for (int i = 0; i < m_Batches.size(); i++)
		{
			m_Batches[i]->Clear();
		}
	}

	void Renderer::i_Update(bool show_info)
	{
		if (m_Batches.back()->getIndicesCount() >= m_Batches.back()->getIndicesMaxCount())
		{
			AddBatch(m_batchSize);
		}

		if (show_info)
		{

			std::cout << "------------------------------------------------------------------" << std::endl;
			std::cout << "Batches: " << m_Batches.size() << std::endl;

			for (Batch* batch : m_Batches)
			{
				batch->Update();
				std::cout << "Vetices: " << batch->getVerticesCount() << std::endl;
				std::cout << "Indices: " << batch->getIndicesCount() << std::endl;
			}
			std::cout << "------------------------------------------------------------------" << std::endl;
		}
		else
		{
			for (Batch* batch : m_Batches)
			{
				batch->Update();
			}
		}
	}

	void Renderer::i_Draw(bool show_info)
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

	/*-------------------------- Child Functions --------------------------*/

	Renderer::Batch::Batch(unsigned int batchSize)
	{
		m_BatchSize = batchSize;

		m_vbo.SetSize(batchSize * sizeof(Vertex) * sizeof(GLfloat));
		m_ibo.SetCount(batchSize * 10);

		// Should match the vertex
		m_vbl.Push<GLfloat>(2);
		m_vbl.Push<GLfloat>(4);
		m_vbl.Push<GLfloat>(2);
		m_vbl.Push<GLfloat>(1);

		m_vao.AddBuffer(m_vbo, m_vbl);
		m_ibo.Bind();

	}

	Renderer::Batch::~Batch()
	{
	}

	void Renderer::Batch::AddRenderable(Renderable& renderable, const char* id)
	{
		if (!m_indices.empty())
		{
			auto to_add = *std::max_element(m_indices.begin(), m_indices.end()) + 1;
			for (int i = 0; i < renderable.m_indices.size(); i++)
			{
				renderable.m_indices[i] += to_add;
			}
		}

		m_vertices.insert(m_vertices.end(), renderable.m_vertices.begin(), renderable.m_vertices.end());
		m_indices.insert(m_indices.end(), renderable.m_indices.begin(), renderable.m_indices.end());
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
};