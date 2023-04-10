#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "engine/utils/math/Math.h"
#include "engine/rendering/geometry/Geometry.h"

class Rect : public Geometry
{

	friend class Renderer;

public:
	Rect(Vertex center, float width, float height);
	Rect(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
	~Rect();

	void SetColor(Color color);
	void SetGradient(Color c1, Color c2, Color c3, Color c4);

	glm::mat4 getModel();

	void Translate(float x, float y);
	void Scale(float x, float y) {}
	void Rotate(float angle) {}
private:
	glm::mat4 m_Model = glm::mat4(1.0f);
};

