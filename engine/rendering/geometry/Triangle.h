#pragma once

#include "engine/rendering/geometry/Geometry.h"

class Triangle : public Geometry
{
	friend class Renderer;

public:
	Triangle(Vertex v1, Vertex v2, Vertex v3);
	~Triangle();

	void Draw(Renderer& renderer, int x, int y) {}

	void SetPos(int x, int y) {}
	void SetColor(Color color);
	void SetGradient(Color v1, Color v2, Color v3);

	void Translate(float x, float y);
	void Scale(float x, float y) {}
	void Rotate(float angle) {}
};

