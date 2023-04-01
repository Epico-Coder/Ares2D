#pragma once

#include <vector>

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

#include "engine/rendering/storage/VertexArray.h"
#include "engine/rendering/storage/IndexBuffer.h"
#include "engine/rendering/storage/FrameBuffer.h"
#include "engine/rendering/storage/RenderBuffer.h"

struct Entity
{
	
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	void DrawTestTriangle(float x, float y, float size) const;
private:
	std::vector<Entity> m_Entities;
};

