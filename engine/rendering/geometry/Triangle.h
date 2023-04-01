#pragma once

#include <vector>

#include "dependancies/glew/include/GL/glew.h"
#include "engine/utils/color/Color.h"

struct TrianglePS
{
	float x1;
	float y1;

	float x2;
	float y2;

	float x3;
	float y3;
};

class Triangle
{
public:
	Triangle(TrianglePS triangle_ps, Color color, float texID);
	~Triangle();

	void SetColor(Color color);
	void SetGradient(Color v1, Color v2, Color v3);
public:
	std::vector<float> getPosition();
	std::vector<unsigned int> getIndices();
protected:
	std::vector<float> m_position;
	std::vector<unsigned int> m_indices;
};

