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


struct EntityStruct
{
	std::string m_id;
	std::vector<float> m_vertexVec;
	std::vector<unsigned int> m_indexVec;

	void set_vertex(std::vector<float> vertex) { m_vertexVec = vertex; }
	void set_index(std::vector<unsigned int> index) { m_indexVec = index; }
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	void DrawTestTriangle(float x, float y, float size) const;

	template <typename T>
	void AddGeometry(Geometry* geometry, const char* id = nullptr) {}
	template<>
	void AddGeometry<Triangle>(Geometry* geometry, const char* id);
	template<>
	void AddGeometry<Rect>(Geometry* geometry, const char* id);

	void Update();

	void Draw();
	
private:
	std::vector<EntityStruct> m_Entities;

	std::vector<Geometry*> m_Geometries;
public:
	unsigned int m_triangles_no = 0;
	unsigned int m_rect_no = 0;
	unsigned int m_circle_no = 0;
	unsigned int m_polygon_no = 0;
private:
	// Contains positions and corresponding indices of every object on screen
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;

	VertexArray m_vao;
	VertexBuffer m_vbo;
	VertexBufferLayout m_vbl;
	//IndexBuffer m_ibo;
};

