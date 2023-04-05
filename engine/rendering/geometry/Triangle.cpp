#include "Triangle.h"

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3, unsigned int triNo)
{
	for (Vertex vertex : {v1, v2, v3})
	{
		for (float f : vertex.Position)
			m_vertices.push_back(f);
		for (float f : vertex.mColor)
			m_vertices.push_back(f);
		for (float f : vertex.TexCords)
			m_vertices.push_back(f);
		m_vertices.push_back(vertex.TexID);
	}

	m_indices = { 0 + (triNo * 3), 1 + (triNo * 3), 2 + (triNo * 3) };
}

void Triangle::SetColor(Color color)
{
	for (int i = 0; i < 3; i++)
	{
		m_vertices[2 + (9 * i)] = color.r;
		m_vertices[3 + (9 * i)] = color.g;
		m_vertices[4 + (9 * i)] = color.b;
		m_vertices[5 + (9 * i)] = color.a;
	}
}

void Triangle::SetGradient(Color v1, Color v2, Color v3)
{
	std::vector<Color>gradient = { v1, v2, v3 };
	for (int i = 0; i < 3; i++)
	{
		m_vertices[2 + (9 * i)] = gradient[i].r;
		m_vertices[3 + (9 * i)] = gradient[i].g;
		m_vertices[4 + (9 * i)] = gradient[i].b;
		m_vertices[5 + (9 * i)] = gradient[i].a;
	}
}

void Triangle::Translate(float x, float y)
{
	m_vertices[0] += x;
	m_vertices[1] += y;
	m_vertices[9] += x;
	m_vertices[10] += y;
	m_vertices[18] += x;
	m_vertices[19] += y;
}

Triangle::~Triangle()
{
}
