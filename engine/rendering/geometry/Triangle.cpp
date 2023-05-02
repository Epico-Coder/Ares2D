#include "Triangle.h"

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3)
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

	m_indices = { 0, 1, 2 };
}

void Triangle::SetColor(Color color)
{
	for (int i = 0; i < 3; i++)
	{
		m_vertices[2 + (10 * i)] = color.r;
		m_vertices[3 + (10 * i)] = color.g;
		m_vertices[4 + (10 * i)] = color.b;
		m_vertices[5 + (10 * i)] = color.a;
	}
}

void Triangle::SetGradient(Color c1, Color c2, Color c3)
{
	std::vector<Color>gradients = { c1, c2, c3 };
	for (int i = 0; i < 3; i++)
	{
		m_vertices[2 + (10 * i)] = gradients[i].r;
		m_vertices[3 + (10 * i)] = gradients[i].g;
		m_vertices[4 + (10 * i)] = gradients[i].b;
		m_vertices[5 + (10 * i)] = gradients[i].a;
	}
}

void Triangle::Translate(float x, float y)
{
	for (int i = 0; i < 3; i++)
	{
		m_vertices[0 + (10 * i)] += x;
		m_vertices[1 + (10 * i)] += y;
	}
}

Triangle::~Triangle()
{
}
