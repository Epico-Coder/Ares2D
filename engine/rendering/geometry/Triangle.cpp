#include "Triangle.h"

namespace Ares2D
{
	Triangle::Triangle()
	{
		m_position[0] = Ares2D::Float2{ 0, 0 };
		m_position[1] = Ares2D::Float2{ 0, 0 };
		m_position[2] = Ares2D::Float2{ 0, 0 };

		m_color = { 0, 0, 0, 0 };

		// Only used for setting empty vectors
		Vertex v1{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
		Vertex v2{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
		Vertex v3{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

		for (Vertex vertex : {v1, v2, v3})
		{
			for (float f : vertex.Position)
				m_vertices.push_back(f);
			for (float f : vertex.Color)
				m_vertices.push_back(f);
			for (float f : vertex.TexCords)
				m_vertices.push_back(f);
			m_vertices.push_back(vertex.TexID);
		}

		m_indices = { 0, 1, 2 };
		m_og_vertices = m_vertices;
	}

	Triangle::Triangle(Ares2D::Float2 p1, Ares2D::Float2 p2, Ares2D::Float2 p3, Ares2D::Color4 color, TextureUse texture_use)
	{
		m_position[0] = p1;
		m_position[1] = p2;
		m_position[2] = p3;

		Vertex v1{ p1.x, p1.y, color.r, color.g, color.b, color.a, texture_use.m_tex_cords[0].first, texture_use.m_tex_cords[0].second, texture_use.m_texture_id };
		Vertex v2{ p2.x, p2.y, color.r, color.g, color.b, color.a, texture_use.m_tex_cords[1].first, texture_use.m_tex_cords[1].second, texture_use.m_texture_id };
		Vertex v3{ p3.x, p3.y, color.r, color.g, color.b, color.a, texture_use.m_tex_cords[2].first, texture_use.m_tex_cords[2].second, texture_use.m_texture_id };

		for (Vertex vertex : {v1, v2, v3})
		{
			for (float f : vertex.Position)
				m_vertices.push_back(f);
			for (float f : vertex.Color)
				m_vertices.push_back(f);
			for (float f : vertex.TexCords)
				m_vertices.push_back(f);
			m_vertices.push_back(vertex.TexID);
		}

		m_indices = { 0, 1, 2 };
		m_og_vertices = m_vertices;
	}

	Triangle::Triangle(Ares2D::Float2 p1, Ares2D::Float2 p2, Ares2D::Float2 p3, Ares2D::Color4 color)
	{
		m_position[0] = p1;
		m_position[1] = p2;
		m_position[2] = p3;

		Vertex v1{ p1.x, p1.y, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f };
		Vertex v2{ p2.x, p2.y, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f };
		Vertex v3{ p3.x, p3.y, color.r, color.g, color.b, color.a, 0.0f, 0.0f, 0.0f };

		for (Vertex vertex : {v1, v2, v3})
		{
			for (float f : vertex.Position)
				m_vertices.push_back(f);
			for (float f : vertex.Color)
				m_vertices.push_back(f);
			for (float f : vertex.TexCords)
				m_vertices.push_back(f);
			m_vertices.push_back(vertex.TexID);
		}

		m_indices = { 0, 1, 2 };
		m_og_vertices = m_vertices;
	}

	Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b, float a)
	{
		m_position[0] = Ares2D::Float2{ x1, y1 };
		m_position[1] = Ares2D::Float2{ x2, y2 };
		m_position[2] = Ares2D::Float2{ x3, y3 };

		m_color = Ares2D::Color4{ r, g, b, a };

		Vertex v1{ x1, y1, r, g, b, a, 0.0f, 0.0f, 0.0f };
		Vertex v2{ x2, y2, r, g, b, a, 0.0f, 0.0f, 0.0f };
		Vertex v3{ x3, y3, r, g, b, a, 0.0f, 0.0f, 0.0f };

		for (Vertex vertex : {v1, v2, v3})
		{
			for (float f : vertex.Position)
				m_vertices.push_back(f);
			for (float f : vertex.Color)
				m_vertices.push_back(f);
			for (float f : vertex.TexCords)
				m_vertices.push_back(f);
			m_vertices.push_back(vertex.TexID);
		}

		m_indices = { 0, 1, 2 };
		m_og_vertices = m_vertices;

	}

	Triangle::~Triangle()
	{

	}

	Ares2D::Float2 Triangle::GetSize()
	{
		return Ares2D::Float2{ 0.0f, 0.0f };
	}

	void Triangle::SetSize(Ares2D::Float2 size)
	{

	}

	Ares2D::Float2 Triangle::GetPos()
	{
		return Ares2D::Float2{ (m_position[0].x + m_position[1].x + m_position[2].x) / 3, (m_position[0].y + m_position[1].y + m_position[2].y) / 3 };
	}

	void Triangle::SetPos(Ares2D::Float2 p1, Ares2D::Float2 p2, Ares2D::Float2 p3)
	{
		m_position[0] = p1;
		m_position[1] = p2;
		m_position[2] = p3;

		for (int i = 0; i < 3; i++)
		{
			m_vertices[0 + (vertex_num * i)] = m_position[i].x;
			m_vertices[1 + (vertex_num * i)] = m_position[i].y;
		}

		m_og_vertices = m_vertices;
	}

	Ares2D::Color4 Triangle::GetColor()
	{
		return m_color;
	}

	void Triangle::SetColor(Ares2D::Color4 color)
	{
		m_color = color;

		for (int i = 0; i < 3; i++)
		{
			m_vertices[2 + (vertex_num * i)] = color.r;
			m_vertices[3 + (vertex_num * i)] = color.g;
			m_vertices[4 + (vertex_num * i)] = color.b;
			m_vertices[5 + (vertex_num * i)] = color.a;
		}
	}

	void Triangle::SetGradient(Ares2D::Color4 c1, Ares2D::Color4 c2, Ares2D::Color4 c3, Ares2D::Color4 c4)
	{
		m_color = c1;

		std::vector<Ares2D::Color4> colors = { c1, c2, c3, c4 };
		for (int i = 0; i < 3; i++)
		{
			m_vertices[2 + (vertex_num * i)] = colors[i].r;
			m_vertices[3 + (vertex_num * i)] = colors[i].g;
			m_vertices[4 + (vertex_num * i)] = colors[i].b;
			m_vertices[5 + (vertex_num * i)] = colors[i].a;
		}

		m_og_vertices = m_vertices;
	}

	Ares2D::Float2 Triangle::GetTranslation()
	{
		return m_translation;
	}

	void Triangle::SetTranslation(Ares2D::Float2 translation)
	{
		m_translation = translation;

		for (int i = 0; i < 3; ++i)
		{
			m_vertices[0 + (vertex_num * i)] += m_translation.x;
			m_vertices[1 + (vertex_num * i)] += m_translation.y;

			m_position[i] = Ares2D::Float2{ m_vertices[0 + (vertex_num * i)], m_vertices[1 + (vertex_num * i)] };
		}
	}

	void Triangle::Translate(Ares2D::Float2 translation)
	{
		SetTranslation(m_translation + translation);
	}

	Ares2D::Float2 Triangle::GetScale()
	{
		return m_scale;
	}

	void Triangle::SetScale(Ares2D::Float2 scale)
	{
		m_scale = scale;

		// Compute the center of the Triangle
		Ares2D::Float2 center{ (m_position[0].x + m_position[1].x + m_position[2].x) / 3, (m_position[0].y + m_position[1].y + m_position[2].y) / 3 };

		// scale the vertices relative to the center of the Triangle
		for (int i = 0; i < 3; ++i)
		{
			Ares2D::Float2 position{ m_vertices[0 + (vertex_num * i)], m_vertices[1 + (vertex_num * i)] };

			position -= center;
			position *= m_scale;
			position += center;

			m_vertices[0 + (vertex_num * i)] = position.x;
			m_vertices[1 + (vertex_num * i)] = position.y;

			m_position[i] = Ares2D::Float2{ m_vertices[0 + (vertex_num * i)], m_vertices[1 + (vertex_num * i)] };
		}
	}

	void Triangle::Scale(Ares2D::Float2 scale)
	{
		SetScale(m_scale + scale);
	}

	float Triangle::GetAngle()
	{
		return m_angle;
	}

	void Triangle::SetAngle(float angle)
	{

		SetAngle(angle, Ares2D::Float2{ (m_position[0].x + m_position[1].x + m_position[2].x) / 3, (m_position[0].y + m_position[1].y + m_position[2].y) / 3 });
		/*
		// Compute the rotation matrix
		glm::mat2 rotationMatrix = glm::mat2(glm::vec2(cos(angle), -sin(angle)), glm::vec2(sin(angle), cos(angle)));

		// Compute the rotation point (center of the Triangleangle)
		glm::vec2 center{ (m_position[0].x + m_position[1].x + m_position[2].x) / 3, (m_position[0].y + m_position[1].y + m_position[2].y) / 3 };

		// Rotate each vertex using the original positions as reference
		for (int i = 0; i < 3; ++i)
		{
			glm::vec2 newPos = RotateVertex(m_og_vertices[0 + (vertex_num * i)], m_og_vertices[1 + (vertex_num * i)], center, rotationMatrix);
			m_vertices[0 + (vertex_num * i)] = newPos.x;
			m_vertices[1 + (vertex_num * i)] = newPos.y;

			m_position[i] = Ares2D::Float2{ m_vertices[0 + (vertex_num * i)], m_vertices[1 + (vertex_num * i)] };
		}

		// Update the current angle
		m_angle = angle;
		*/
	}

	void Triangle::SetAngle(float angle, Ares2D::Float2 center)
	{
		// Compute the rotation matrix
		glm::mat2 rotationMatrix = glm::mat2(glm::vec2(cos(angle), -sin(angle)), glm::vec2(sin(angle), cos(angle)));

		// Rotate each vertex using the original positions as reference
		for (int i = 0; i < 3; ++i)
		{
			glm::vec2 newPos = RotateVertex(m_og_vertices[0 + (vertex_num * i)], m_og_vertices[1 + (vertex_num * i)], glm::vec2{ center.x, center.y }, rotationMatrix);
			m_vertices[0 + (vertex_num * i)] = newPos.x;
			m_vertices[1 + (vertex_num * i)] = newPos.y;

			m_position[i] = Ares2D::Float2{ m_vertices[0 + (vertex_num * i)], m_vertices[1 + (vertex_num * i)] };

			m_og_vertices = m_vertices;
		}

		// Update the current angle
		m_angle = angle;
	}

	void Triangle::Rotate(float angle)
	{
		SetAngle(m_angle + angle);
	}

	void Triangle::Rotate(float angle, Ares2D::Float2 center)
	{
		SetAngle(m_angle + angle, center);
	}

	glm::vec2 Triangle::RotateVertex(float x, float y, const glm::vec2& rotationPoint, const glm::mat2& rotationMatrix)
	{
		glm::vec2 position{ x, y };

		position -= rotationPoint;
		position = rotationMatrix * position;
		position += rotationPoint;

		return position;
	}
};