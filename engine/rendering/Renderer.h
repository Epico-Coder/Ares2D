#pragma once

#include <vector>

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

#include "engine/rendering/storage/VertexArray.h"
#include "engine/rendering/storage/IndexBuffer.h"
#include "engine/rendering/storage/FrameBuffer.h"
#include "engine/rendering/storage/RenderBuffer.h"

#include "engine/rendering/geometry/Triangle.h"
#include "engine/rendering/geometry/Rect.h"
#include "engine/rendering/geometry/Circle.h"
#include "engine/rendering/geometry/Polygon.h"


struct EntityStruct
{
	const char* m_id;
	std::vector<float> m_positionVec;
	std::vector<unsigned int> m_indexVec;
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	void DrawTestTriangle(float x, float y, float size) const;

	void AddTriangle(const char* id, Triangle& triangle);
	void UpdateTriangle(const char* id, Triangle& triangle);

	void Draw();

private:
	std::vector<EntityStruct> m_Entities;

	// Contains positions and corresponding indices of every object on screen
	std::vector<float> m_positions;
	std::vector<unsigned int> m_indices;

	// VertexBuffer m_vbo;
	VertexBufferLayout m_vbl;
	VertexArray m_vao;
	// IndexBuffer m_ibo;
};

