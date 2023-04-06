#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "engine/rendering/geometry/Geometry.h"

#pragma once

#include "dependancies/glew/include/GL/glew.h"
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

	void Translate(float x, float y);
	void Scale(float x, float y) {}
	void Rotate(float angle) {}
};

