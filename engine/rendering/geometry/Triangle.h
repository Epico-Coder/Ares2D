#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "engine/rendering/geometry/Geometry.h"

struct TrianglePS
{
	float x1;
	float y1;

	float x2;
	float y2;

	float x3;
	float y3;
};

class Triangle : public Geometry
{

	friend class Renderer;

public:
	Triangle(Vertex v1, Vertex v2, Vertex v3);
	~Triangle();

	void SetColor(Color color);
	void SetGradient(Color v1, Color v2, Color v3);

	void Translate(float x, float y);
	void Scale(float x, float y) {}
	void Rotate(float angle) {}
};

