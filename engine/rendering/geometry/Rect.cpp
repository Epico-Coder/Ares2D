#include "Rect.h"

Rect::Rect()
{
	// Only used for setting empty vectors
	Vertex v1{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	Vertex v2{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	Vertex v3{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	Vertex v4{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

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

Rect::Rect(Position position, Color color, TextureUse texture_use)
{
	m_width = position.w;
	m_height = position.h;

	Vertex v1{ position.x			  , position.y			   , color.r, color.g, color.b, color.a, texture_use.m_tex_cords[0].first, texture_use.m_tex_cords[0].second, texture_use.m_texture_id };
	Vertex v2{ position.x + position.w, position.y			   , color.r, color.g, color.b, color.a, texture_use.m_tex_cords[1].first, texture_use.m_tex_cords[1].second, texture_use.m_texture_id };
	Vertex v3{ position.x + position.w, position.y + position.h, color.r, color.g, color.b, color.a, texture_use.m_tex_cords[2].first, texture_use.m_tex_cords[2].second, texture_use.m_texture_id };
	Vertex v4{ position.x			  , position.y + position.h, color.r, color.g, color.b, color.a, texture_use.m_tex_cords[3].first, texture_use.m_tex_cords[3].second, texture_use.m_texture_id };

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

Rect::Rect(Position position, Color color, float TexID)
{
	m_width = position.w;
	m_height = position.h;

	Vertex v1{ position.x			  , position.y			   , color.r, color.g, color.b, color.a, 0.0f, 0.0f, TexID };
	Vertex v2{ position.x + position.w, position.y			   , color.r, color.g, color.b, color.a, 0.0f, 0.0f, TexID };
	Vertex v3{ position.x + position.w, position.y + position.h, color.r, color.g, color.b, color.a, 0.0f, 0.0f, TexID };
	Vertex v4{ position.x			  , position.y + position.h, color.r, color.g, color.b, color.a, 0.0f, 0.0f, TexID };

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

Rect::Rect(float x, float y, float width, float height, float r, float g, float b, float a, float TexID)
{
	m_width = width;
	m_height = height;

	Vertex v1{ x	    , y			, r, g, b, a, 0.0f, 0.0f, TexID };
	Vertex v2{ x + width, y			, r, g, b, a, 1.0f, 0.0f, TexID };
	Vertex v3{ x + width, y + height, r, g, b, a, 1.0f, 1.0f, TexID };
	Vertex v4{ x		, y + height, r, g, b, a, 0.0f, 1.0f, TexID };

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

void Rect::Add(Renderer& renderer)
{
	renderer.AddRenderable(*this);
}

void Rect::Add(Renderer& renderer, int x, int y)
{
	SetPos(x, y);
	renderer.AddRenderable(*this);
}

void Rect::SetPos(int x, int y)
{
	m_vertices[0 + (vertex_num * 0)] = x - m_width / 2;
	m_vertices[1 + (vertex_num * 0)] = y - m_height / 2;
	m_vertices[0 + (vertex_num * 1)] = x + m_width / 2;
	m_vertices[1 + (vertex_num * 1)] = y - m_height / 2;
	m_vertices[0 + (vertex_num * 2)] = x + m_width / 2;
	m_vertices[1 + (vertex_num * 2)] = y + m_height / 2;
	m_vertices[0 + (vertex_num * 3)] = x - m_width / 2;
	m_vertices[1 + (vertex_num * 3)] = y + m_height / 2;
}

void Rect::SetColor(Color color)
{
	for (int i = 0; i < 4; i++)
	{
		m_vertices[2 + (vertex_num * i)] = color.r;
		m_vertices[3 + (vertex_num * i)] = color.g;
		m_vertices[4 + (vertex_num * i)] = color.b;
		m_vertices[5 + (vertex_num * i)] = color.a;
	}
}

void Rect::SetGradient(Color c1, Color c2, Color c3, Color c4)
{
	std::vector<Color>gradients = { c1, c2, c3, c4 };
	for (int i = 0; i < 4; i++)
	{
		m_vertices[2 + (vertex_num * i)] = gradients[i].r;
		m_vertices[3 + (vertex_num * i)] = gradients[i].g;
		m_vertices[4 + (vertex_num * i)] = gradients[i].b;
		m_vertices[5 + (vertex_num * i)] = gradients[i].a;
	}
}

void Rect::SetTexCords(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	std::vector<std::vector<float>>tex_cords {{ x1, y1 },
											  { x2, y2 },
											  { x3, y3 },
											  { x4, y4 }};
	for (int i = 0; i < 4; i++)
	{
		m_vertices[6 + (vertex_num * i)] = tex_cords[i][0];
		m_vertices[7 + (vertex_num * i)] = tex_cords[i][1];
	}
}

void Rect::SetTexID(unsigned int TexID)
{
	for (int i = 0; i < 4; i++)
	{
		m_vertices[8 + (vertex_num * i)] = TexID;
	}
}

glm::mat4 Rect::getModel()
{
	return m_Model;
}

void Rect::Translate(float x, float y)
{
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
	m_Model *= translation;
}
