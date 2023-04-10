#pragma once

#include <vector>
#include <string>

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

#include "engine/rendering/storage/VertexBuffer.h"
#include "engine/rendering/storage/VertexBufferLayout.h"
#include "engine/rendering/storage/VertexArray.h"
#include "engine/rendering/storage/IndexBuffer.h"
#include "engine/rendering/storage/FrameBuffer.h"
#include "engine/rendering/storage/RenderBuffer.h"

#include "engine/rendering/geometry/Geometry.h"
#include "engine/rendering/geometry/Triangle.h"
#include "engine/rendering/geometry/Rect.h"
#include "engine/rendering/geometry/Circle.h"
#include "engine/rendering/geometry/Polygon.h"

class Renderer
{
	friend class Geometry;

public:
	Renderer(unsigned int batchSize = 1000);
	~Renderer();

	void DrawTestTriangle(float x, float y, float size) const;

	template <typename T>
	void AddGeometry(Geometry& geometry, const char* id = nullptr) {}
	template<>
	void AddGeometry<Triangle>(Geometry& geometry, const char* id);
	template<>
	void AddGeometry<Rect>(Geometry& geometry, const char* id);

	void Update();

	void Draw();
public:
	unsigned int m_triangle_no = 0;
private:
	class Batch
	{
	public:
		Batch(unsigned int batchSize = 1000);
		~Batch();

		int getGeometryCount() { return m_Geometries.size(); }
		int getVerticesCount() { return m_vertices.size(); }
		int getIndicesCount() { return m_indices.size(); }
		int getIndicesMaxCount() { return m_ibo.GetCount(); }

		template <typename T>
		void AddGeometry(Geometry& geometry, const char* id = nullptr) {}
		template<>
		void AddGeometry<Triangle>(Geometry& geometry, const char* id);
		template<>
		void AddGeometry<Rect>(Geometry& geometry, const char* id);

		void Update();
		void Draw();
	private:
		unsigned int m_BatchSize;

		std::vector<Geometry> m_Geometries;

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


