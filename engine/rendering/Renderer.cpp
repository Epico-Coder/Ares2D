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

	void Renderer::AddRenderable(Renderable* renderable, const char* id)
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
		Instance().i_Draw(show_info);
	}

	/*-------------------------- Internal Functions --------------------------*/

	void Renderer::i_Init(unsigned int batchSize)
	{
		m_BatchSize = batchSize;
		AddBatch(m_BatchSize);
	}

	void Renderer::i_DrawTestTriangle(float x, float y, float size)
	{
		glBegin(GL_TRIANGLES);
		glVertex2f(x - size, y);
		glVertex2f(x + size, y);
		glVertex2f(x, y + (size * 2));
		glEnd();
	}

	void Renderer::i_AddRenderable(Renderable* renderable, const char* id)
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
			AddBatch(m_BatchSize);
		}

		if (show_info)
		{

			std::cout << "------------------------------------------------------------------" << std::endl;
			std::cout << "Batches: " << m_Batches.size() << std::endl;

			for (Batch* batch : m_Batches)
			{
				batch->Update();
				std::cout << "Renderables: " << batch->getRenderableCount() << std::endl;
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
		Update(show_info);

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

		m_vbo.SetSize(m_BatchSize * sizeof(Vertex) * sizeof(GLfloat));

		// Should match the vertex
		m_vbl.Push<GLfloat>(2);
		m_vbl.Push<GLfloat>(4);
		m_vbl.Push<GLfloat>(2);
		m_vbl.Push<GLfloat>(1);
		m_vbl.Push<GLfloat>(1);
		
		m_vao.AddBuffer(m_vbo, m_vbl);

		m_ibo.SetCount(m_BatchSize * 10);

		m_ssbo.SetSize(m_BatchSize * sizeof(glm::mat4));
	}

	Renderer::Batch::~Batch()
	{
	}

	void Renderer::Batch::AddRenderable(Renderable* renderable, const char* id)
	{	
		//std::cout << "Renderable len: " << static_cast<float>(m_renderables.size()) << std::endl;

		m_renderables.push_back(renderable);
	}

	void Renderer::Batch::Clear()
	{
		m_vertices.clear();
		m_indices.clear();
		m_models.clear();
		m_renderables.clear();
	}

	void Renderer::Batch::Update()
	{
		unsigned int vertexOffset = 0;
		unsigned int modelOffset = 0;
		unsigned int indexOffset = 0;
		unsigned int max_index = 0;

		unsigned int instance = 0;

		for (auto& renderable : m_renderables)
		{
			// Adding vertices
			renderable->SetVertices();

			std::vector<Vertex>& vertex_arr = renderable->m_vertices;
			std::vector<float> vertices;

			for (Vertex& vertex : vertex_arr)
			{
				const float* begin = reinterpret_cast<const float*>(&vertex);
				const float* end = begin + sizeof(Vertex) / sizeof(float);
				vertices.insert(vertices.end(), begin, end);
				vertices.push_back(instance);
			}

			m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
			m_vbo.Update(vertices.data(), vertices.size() * sizeof(GLfloat), vertexOffset);
			
			// Adding transformations
			renderable->SetTransform();

			const glm::mat4& transform = renderable->m_transform;
			m_models.insert(m_models.end(), transform);

			m_ssbo.Update(&transform, sizeof(glm::mat4), modelOffset);
			
			// Adding indices
			std::vector<unsigned int> indices = renderable->m_indices;
			
			for (int i = 0; i < indices.size(); i++)
				indices[i] += max_index;

			max_index = std::max(max_index, *std::max_element(indices.begin(), indices.end()) + 1);

			m_indices.insert(m_indices.end(), indices.begin(), indices.end());
			m_ibo.Update(indices.data(), indices.size(), indexOffset);

			// Update the offsets for the next iteration
			vertexOffset += vertices.size() * sizeof(GLfloat);
			modelOffset += sizeof(transform);
			indexOffset += indices.size();

			instance++;
		}

	}

	void Renderer::Batch::Draw()
	{
		m_vao.Bind();
		m_ibo.Bind();
		m_ssbo.BindIndex(0);

		// Draw the shape
		glDrawElements(GL_TRIANGLES, 6*4, GL_UNSIGNED_INT, nullptr);
	}
};
