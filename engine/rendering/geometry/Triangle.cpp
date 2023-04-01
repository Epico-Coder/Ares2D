#include "Triangle.h"

Triangle::Triangle(TrianglePS triangle_ps, Color color, float texID)
{
	m_position = { triangle_ps.x1, triangle_ps.y1, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texID,
				   triangle_ps.x2, triangle_ps.y2, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texID,
				   triangle_ps.x3, triangle_ps.y3, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texID };

	m_indices = { 0, 1, 2 };
}

void Triangle::SetColor(Color color)
{
	for (int i = 0; i < 3; i++)
	{
		m_position[2 + (9 * i)] = color.r;
		m_position[3 + (9 * i)] = color.g;
		m_position[4 + (9 * i)] = color.b;
		m_position[5 + (9 * i)] = color.a;
	}
}

void Triangle::SetGradient(Color v1, Color v2, Color v3)
{
	std::vector<Color>gradient = { v1, v2, v3 };
	for (int i = 0; i < 3; i++)
	{
		m_position[2 + (9 * i)] = gradient[i].r;
		m_position[3 + (9 * i)] = gradient[i].g;
		m_position[4 + (9 * i)] = gradient[i].b;
		m_position[5 + (9 * i)] = gradient[i].a;
	}
}

std::vector<float> Triangle::getPosition()
{
	return m_position;

}

std::vector<unsigned int> Triangle::getIndices()
{
	return m_indices;
}

Triangle::~Triangle()
{
}
