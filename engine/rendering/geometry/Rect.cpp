#include "Rect.h"

Rect::Rect()
{
	m_position = { 0, 0, 0, 0, };
	m_color = { 0, 0, 0, 0 };

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
	m_og_vertices = m_vertices;
}

Rect::Rect(Ares2D::Float4 position, Ares2D::Color4 color, TextureUse texture_use)
{
	m_position = position;
	m_color = color;

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
	m_og_vertices = m_vertices;
}

Rect::Rect(Ares2D::Float4 position, Ares2D::Color4 color)
{
	m_position = position;
	m_color = color;

	Vertex v1{ position.x			  , position.y			   , color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f };
	Vertex v2{ position.x + position.w, position.y			   , color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f };
	Vertex v3{ position.x + position.w, position.y + position.h, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f };
	Vertex v4{ position.x			  , position.y + position.h, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f };

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
	m_og_vertices = m_vertices;
}

Rect::Rect(float x, float y, float width, float height, float r, float g, float b, float a)
{
	m_position = { x, y, width, height };
	m_color = { r, g, b, a };

	Vertex v1{ x	    , y			, r, g, b, a, 0.0f, 0.0f, 0.0f };
	Vertex v2{ x + width, y			, r, g, b, a, 1.0f, 0.0f, 0.0f };
	Vertex v3{ x + width, y + height, r, g, b, a, 1.0f, 1.0f, 0.0f };
	Vertex v4{ x		, y + height, r, g, b, a, 0.0f, 1.0f, 0.0f };

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
	m_og_vertices = m_vertices;
}

Rect::~Rect()
{
}

Ares2D::Float4 Rect::GetRect()
{
	return m_position;
}

Ares2D::Float2 Rect::GetSize()
{
	return Ares2D::Float2{ m_position.w, m_position.h };
}

void Rect::SetSize(Ares2D::Float2 size)
{
}

Ares2D::Float2 Rect::GetPos()
{
	return Ares2D::Float2{ m_position.x, m_position.y };
}

void Rect::SetPos(Ares2D::Float2 pos)
{
	m_position.x = pos.x;
	m_position.y = pos.y;

	m_vertices[0 + (vertex_num * 0)] = pos.x;
	m_vertices[1 + (vertex_num * 0)] = pos.y;
	m_vertices[0 + (vertex_num * 1)] = pos.x + m_position.w;
	m_vertices[1 + (vertex_num * 1)] = pos.y;
	m_vertices[0 + (vertex_num * 2)] = pos.x + m_position.w;
	m_vertices[1 + (vertex_num * 2)] = pos.y + m_position.h;
	m_vertices[0 + (vertex_num * 3)] = pos.x;
	m_vertices[1 + (vertex_num * 3)] = pos.y + m_position.h;

	m_og_vertices = m_vertices;
}

Ares2D::Color4 Rect::GetColor()
{
	return m_color;
}

void Rect::SetColor(Ares2D::Color4 color)
{
	m_color = color;

	for (int i = 0; i < 4; i++)
	{
		m_vertices[2 + (vertex_num * i)] = color.r;
		m_vertices[3 + (vertex_num * i)] = color.g;
		m_vertices[4 + (vertex_num * i)] = color.b;
		m_vertices[5 + (vertex_num * i)] = color.a;
	}
}

void Rect::SetGradient(Ares2D::Color4 c1, Ares2D::Color4 c2, Ares2D::Color4 c3, Ares2D::Color4 c4)
{
	m_color = c1;

	std::vector<Ares2D::Color4> colors = { c1, c2, c3, c4 };
	for (int i = 0; i < 4; i++)
	{
		m_vertices[2 + (vertex_num * i)] = colors[i].r;
		m_vertices[3 + (vertex_num * i)] = colors[i].g;
		m_vertices[4 + (vertex_num * i)] = colors[i].b;
		m_vertices[5 + (vertex_num * i)] = colors[i].a;
	}

	m_og_vertices = m_vertices;
}

Ares2D::Float2 Rect::GetTranslation()
{
	return m_translation;
}

void Rect::SetTranslation(Ares2D::Float2 translation)
{
	m_translation = translation;

	for (int i = 0; i < 4; ++i)
	{
		m_vertices[0 + (vertex_num * i)] += m_translation.x;
		m_vertices[1 + (vertex_num * i)] += m_translation.y;
	}

	m_position = Ares2D::Float4{ m_vertices[0], m_vertices[1], m_vertices[0 + (vertex_num * 1)] - m_vertices[0], m_vertices[1 + (vertex_num * 2)] - m_vertices[1] };
}


void Rect::Translate(Ares2D::Float2 translation)
{
	SetTranslation(m_translation + translation);
}

Ares2D::Float2 Rect::GetScale()
{
	return m_scale;
}

void Rect::SetScale(Ares2D::Float2 scale)
{
	m_scale = scale;

	// Compute the center of the rectangle
	Ares2D::Float2 center = { m_position.x + m_position.w / 2, m_position.y + m_position.h / 2 };

	// scale the vertices relative to the center of the rectangle
	for (int i = 0; i < 4; ++i)
	{
		Ares2D::Float2 position{ m_vertices[0 + (vertex_num * i)], m_vertices[1 + (vertex_num * i)] };

		position -= center;
		position *= m_scale;
		position += center;

		m_vertices[0 + (vertex_num * i)] = position.x;
		m_vertices[1 + (vertex_num * i)] = position.y;
	}

	m_position = Ares2D::Float4{ m_vertices[0], m_vertices[1], m_vertices[0 + (vertex_num * 1)] - m_vertices[0], m_vertices[1 + (vertex_num * 2)] - m_vertices[1] };

}

void Rect::Scale(Ares2D::Float2 scale)
{
	SetScale(m_scale + scale);
}

float Rect::GetAngle()
{
	return m_angle;
}

void Rect::SetAngle(float angle)
{
	// Compute the rotation matrix
	glm::mat2 rotationMatrix = glm::mat2(glm::vec2(cos(angle), -sin(angle)), glm::vec2(sin(angle), cos(angle)));

	// Compute the rotation point (center of the rectangle)
	glm::vec2 center = { m_position.x + m_position.w / 2, m_position.y + m_position.h / 2 };

	// Rotate each vertex using the original positions as reference
	for (int i = 0; i < 4; ++i)
	{
		glm::vec2 newPos = RotateVertex(m_og_vertices[0 + (vertex_num * i)], m_og_vertices[1 + (vertex_num * i)], center, rotationMatrix);
		m_vertices[0 + (vertex_num * i)] = newPos.x;
		m_vertices[1 + (vertex_num * i)] = newPos.y;
	}

	// Update the current angle
	m_angle = angle;

	m_position = Ares2D::Float4{ m_vertices[0], m_vertices[1], m_vertices[0 + (vertex_num * 1)] - m_vertices[0], m_vertices[1 + (vertex_num * 2)] - m_vertices[1] };
}

void Rect::SetAngle(float angle, Ares2D::Float2 center)
{
	// Compute the rotation matrix
	glm::mat2 rotationMatrix = glm::mat2(glm::vec2(cos(angle), -sin(angle)), glm::vec2(sin(angle), cos(angle)));

	// Rotate each vertex using the original positions as reference
	for (int i = 0; i < 4; ++i)
	{
		glm::vec2 newPos = RotateVertex(m_og_vertices[0 + (vertex_num * i)], m_og_vertices[1 + (vertex_num * i)], glm::vec2{center.x, center.y}, rotationMatrix);
		m_vertices[0 + (vertex_num * i)] = newPos.x;
		m_vertices[1 + (vertex_num * i)] = newPos.y;
	}

	// Update the current angle
	m_angle = angle;

	m_position = Ares2D::Float4{ m_vertices[0], m_vertices[1], m_vertices[0 + (vertex_num * 1)] - m_vertices[0], m_vertices[1 + (vertex_num * 2)] - m_vertices[1] };
}

void Rect::Rotate(float angle)
{
	SetAngle(m_angle + angle);
}

void Rect::Rotate(float angle, Ares2D::Float2 center)
{
	SetAngle(m_angle + angle, center);
}

glm::vec2 Rect::RotateVertex(float x, float y, const glm::vec2& rotationPoint, const glm::mat2& rotationMatrix)
{
	glm::vec2 position{ x, y };

	position -= rotationPoint;
	position = rotationMatrix * position;
	position += rotationPoint;

	return position;
}