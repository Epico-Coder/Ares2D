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

#include "engine/resources/resource/Resource.h"


namespace Ares2D
{
	class Renderer
	{
	public:
		static Renderer& Instance();

		Renderer(Renderer const&) = delete;
		void operator=(Renderer const&) = delete;

		static void Init(unsigned int batchSize = 1000);

		static void DrawTestTriangle(float x, float y, float size);

		static void AddRenderable(Renderable renderable, const char* id = nullptr);

		static void Clear();
		static void Update(bool show_info);
		static void Draw(bool show_info = false);
	private:
		Renderer();
		~Renderer();
	private:
		void i_Init(unsigned int batchSize = 1000);

		void i_DrawTestTriangle(float x, float y, float size);

		void i_AddRenderable(Renderable& renderable, const char* id = nullptr);

		void i_Clear();
		void i_Update(bool show_info);
		void i_Draw(bool show_info = false);
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
};