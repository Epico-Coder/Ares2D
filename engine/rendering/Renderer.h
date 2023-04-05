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
	void AddTriangle(const char* id, Triangle& triangle);
	void UpdateTriangle(std::string id, Triangle& triangle);

	void Update();
	void Draw();

private:
	std::vector<EntityStruct> m_Entities;

	// Contains positions and corresponding indices of every object on screen
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;

	VertexArray m_vao;
	VertexBuffer m_vbo;
	VertexBufferLayout m_vbl;
	//IndexBuffer m_ibo;
};

