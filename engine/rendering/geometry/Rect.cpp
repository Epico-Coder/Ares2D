#include "Rect.h"

namespace Ares2D
{
	Rect::Rect()
		: m_vertex_arr(4), m_position(0.0f, 0.0f), m_size(1.0f, 1.0f), m_tex_id(0.0f)
	{
		for (int i = 0; i < 4; i++)
		{
			m_color[i] = Ares2D::Color4(0.0f, 0.0f, 0.0f, 0.0f);
			m_tex_cords[i] = Ares2D::Float2(0.0f, 0.0f);
		}

		SetVertices();

		m_indices = { 0, 1, 2, 2, 3, 0 };
	}

	Rect::Rect(Ares2D::Float4 position, Ares2D::Color4 color, TextureUse texture_use)
		: m_vertex_arr(4), m_position(position.x, position.y), m_size(position.w, position.h), m_tex_id(texture_use.m_texture_id)
	{
		for (int i = 0; i < 4; i++) 
		{
			m_color[i] = color;
			m_tex_cords[i] = Ares2D::Float2(texture_use.m_tex_cords[i].first, texture_use.m_tex_cords[i].second);
		}

		SetVertices();

		m_indices = { 0, 1, 2, 2, 3, 0 };
	}

	Rect::Rect(Ares2D::Float4 position, Ares2D::Color4 color)
		: m_vertex_arr(4), m_position(position.x, position.y), m_size(position.w, position.h), m_tex_id(0.0f)
	{
		for (int i = 0; i < 4; i++) 
		{
			m_color[i] = color;
			m_tex_cords[i] = Ares2D::Float2(0, 0);
		}

		SetVertices();

		m_indices = { 0, 1, 2, 2, 3, 0 };
	}

	Rect::Rect(float x, float y, float width, float height, float r, float g, float b, float a)
		: m_vertex_arr(4), m_position(x, y), m_size(width, height), m_tex_id(0.0f)
	{
		Ares2D::Color4 color(r, g, b, a);
		for (int i = 0; i < 4; i++) 
		{
			m_color[i] = color;
			m_tex_cords[i] = Ares2D::Float2(i % 2, i / 2);
		}

		SetVertices();

		m_indices = { 0, 1, 2, 2, 3, 0 };
	}

	Rect::~Rect()
	{
	}

	void Rect::SetVertices()
	{
		glm::vec3 rotationCenter = glm::vec3(m_position.x + m_size.x / 2, m_position.y + m_size.y / 2, 0.0f);

		glm::mat4 transform = glm::mat4(1.0f);

		transform = glm::scale(transform, glm::vec3(m_scale.x, m_scale.y, 1.0f));

		transform = glm::translate(transform, -rotationCenter);
		transform = glm::rotate(transform, m_angle, glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::translate(transform, rotationCenter);
		
		transform = glm::translate(transform, glm::vec3(m_translation.x, m_translation.y, 0.0f));

		m_transform = transform;

		m_vertex_arr[0] = Vertex{ m_position.x		     , m_position.y			  , m_color[0].r, m_color[0].g, m_color[0].b, m_color[0].a, m_tex_cords[0].x, m_tex_cords[0].y, m_tex_id };
		m_vertex_arr[1] = Vertex{ m_position.x + m_size.x, m_position.y			  , m_color[1].r, m_color[1].g, m_color[1].b, m_color[1].a, m_tex_cords[1].x, m_tex_cords[1].y, m_tex_id };
		m_vertex_arr[2] = Vertex{ m_position.x + m_size.x, m_position.y + m_size.y, m_color[2].r, m_color[2].g, m_color[2].b, m_color[2].a, m_tex_cords[2].x, m_tex_cords[2].y, m_tex_id };
		m_vertex_arr[3] = Vertex{ m_position.x		     , m_position.y + m_size.y, m_color[3].r, m_color[3].g, m_color[3].b, m_color[3].a, m_tex_cords[3].x, m_tex_cords[3].y, m_tex_id };
	
		m_vertices.clear();

		for (Vertex vertex : m_vertex_arr)
		{
			for (float f : vertex.Position)
				m_vertices.push_back(f);
			for (float f : vertex.Color)
				m_vertices.push_back(f);
			for (float f : vertex.TexCords)
				m_vertices.push_back(f);
			m_vertices.push_back(vertex.TexID);
		}
		
	}

	Ares2D::Float2 Rect::GetSize()
	{
		return m_size;
	}

	void Rect::SetSize(Ares2D::Float2 size)
	{
		m_size = size;

		SetVertices();
	}

	Ares2D::Float2 Rect::GetPos()
	{
		return m_position;
	}

	void Rect::SetPos(Ares2D::Float2 pos)
	{
		m_position = pos;

		SetVertices();
	}

	Ares2D::Color4 Rect::GetColor()
	{
		// returns mix of 4 corner colors
		return (m_color[0] + m_color[1] + m_color[2] + m_color[3]) / 4;
	}

	void Rect::SetColor(Ares2D::Color4 color)
	{
		for (int i = 0; i < 4; i++)
		{
			m_color[i] = color;
		}

		SetVertices();
	}

	void Rect::SetGradient(Ares2D::Color4 c1, Ares2D::Color4 c2, Ares2D::Color4 c3, Ares2D::Color4 c4)
	{
		m_color[0] = c1;
		m_color[1] = c2;
		m_color[2] = c3;
		m_color[3] = c4;

		SetVertices();
	}

	Ares2D::Float2 Rect::GetTranslation()
	{
		return m_translation;
	}

	void Rect::SetTranslation(Ares2D::Float2 translation)
	{
		m_translation = translation;

		SetVertices();
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

		SetVertices();
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
		m_angle = angle;

		SetVertices();
	}

	void Rect::Rotate(float angle)
	{
		SetAngle(m_angle + angle);
	}
};