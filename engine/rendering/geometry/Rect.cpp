#include "Rect.h"

Rect::Rect(Vertex center, float width, float height)
{
	Vertex v1{ center.Position[0] - width / 2, center.Position[1] - height / 2, center.mColor[0], center.mColor[1], center.mColor[2], center.mColor[3], 0.0f, 0.0f, center.TexID};
	Vertex v2{ center.Position[0] + width / 2, center.Position[1] - height / 2, center.mColor[0], center.mColor[1], center.mColor[2], center.mColor[3], 1.0f, 0.0f, center.TexID };
	Vertex v3{ center.Position[0] + width / 2, center.Position[1] + height / 2, center.mColor[0], center.mColor[1], center.mColor[2], center.mColor[3], 1.0f, 1.0f, center.TexID };
	Vertex v4{ center.Position[0] - width / 2, center.Position[1] + height / 2, center.mColor[0], center.mColor[1], center.mColor[2], center.mColor[3], 0.0f, 1.0f, center.TexID };

	for (Vertex vertex : {v1, v2, v3, v4})
	{
		for (float f : vertex.Position)
			m_vertices.push_back(f);
		for (float f : vertex.mColor)
			m_vertices.push_back(f);
		for (float f : vertex.TexCords)
			m_vertices.push_back(f);
		m_vertices.push_back(vertex.TexID);
	}

	m_indices = { 0, 1, 2, 2, 3, 0 };
}

Rect::Rect(Vertex v1, Vertex v2, Vertex v3, Vertex v4)
{
	for (Vertex vertex : {v1, v2, v3, v4})
	{
		for (float f : vertex.Position)
			m_vertices.push_back(f);
		for (float f : vertex.mColor)
			m_vertices.push_back(f);
		for (float f : vertex.TexCords)
			m_vertices.push_back(f);
		m_vertices.push_back(vertex.TexID);
	}

	m_indices = { 0, 1, 2, 2, 3, 0 };
}

Rect::~Rect()
{
}

void Rect::SetColor(Color color)
{
	for (int i = 0; i < 4; i++)
	{
		m_vertices[2 + (9 * i)] = color.r;
		m_vertices[3 + (9 * i)] = color.g;
		m_vertices[4 + (9 * i)] = color.b;
		m_vertices[5 + (9 * i)] = color.a;
	}
}

void Rect::SetGradient(Color c1, Color c2, Color c3, Color c4)
{
	std::vector<Color>gradients = { c1, c2, c3, c4 };
	for (int i = 0; i < 4; i++)
	{
		m_vertices[2 + (9 * i)] = gradients[i].r;
		m_vertices[3 + (9 * i)] = gradients[i].g;
		m_vertices[4 + (9 * i)] = gradients[i].b;
		m_vertices[5 + (9 * i)] = gradients[i].a;
	}
}

void Rect::Translate(float x, float y)
{
	for (int i = 0; i < 4; i++)
	{
		m_vertices[0 + (9 * i)] += x;
		m_vertices[1 + (9 * i)] += y;
	}
}
