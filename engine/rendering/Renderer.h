#pragma once

#include <vector>
#include <string>

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

#include "engine/rendering/storage/VertexBuffer.h"
#include "engine/rendering/storage/VertexBufferLayout.h"
#include "engine/rendering/storage/VertexArray.h"
#include "engine/rendering/storage/IndexBuffer.h"

#include "engine/rendering/Renderable.h"

#include "engine/utils/error/ErrorHandling.h"

#include "engine/utils/color/Color.h"
#include "engine/utils/math/Math.h"

class Renderer
{
	friend class Renderable;

public:
	Renderer();
	~Renderer();

	void Init(unsigned int batchSize = 1000);

	void DrawTestTriangle(float x, float y, float size) const;

	void AddRenderable(Renderable renderable, const char* id = nullptr);

	void Clear();
	void Update(bool show_info);
	void Draw(bool show_info=false);
private:
	class Batch
	{
	public:
		Batch(unsigned int batchSize = 1000);
		~Batch();

		//int getRenderableCount() { return m_Geometries.size(); }
		int getVerticesCount() { return m_vertices.size(); }
		int getIndicesCount() { return m_indices.size(); }
		int getIndicesMaxCount() { return m_ibo.GetCount(); }

		void AddRenderable(Renderable& renderable, const char* id = nullptr);
		
		void Clear();
		void Update();
		void Draw();
	private:
		unsigned int m_BatchSize;

		//std::vector<Renderable> m_Geometries;

		std::vector<float> m_vertices;
		std::vector<unsigned int> m_indices;

		VertexBuffer m_vbo;
		IndexBuffer m_ibo;
		VertexArray m_vao;
		VertexBufferLayout m_vbl;
	};

	void AddBatch(unsigned int batchSize);
private:
	std::vector<Batch*> m_Batches;
	unsigned int m_batchSize;
};


