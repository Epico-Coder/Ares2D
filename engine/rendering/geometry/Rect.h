#pragma once

#include "engine/rendering/geometry/Geometry.h"
#include "engine/rendering/Renderer.h"
#include <vector>

namespace Ares2D
{
	class Rect : public Geometry
	{
		friend class Renderer;
	public:
		Rect();

		Rect(Ares2D::Float4 position, Ares2D::Color4 color, TextureUse texture_use);
		Rect(Ares2D::Float4 position, Ares2D::Color4 color);
		Rect(float x, float y, float width, float height, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);

		~Rect();

		Ares2D::Float2 GetSize();
		void SetSize(Ares2D::Float2 size);

		Ares2D::Float2 GetPos();
		void SetPos(Ares2D::Float2 pos);

		Ares2D::Color4 GetColor();
		void SetColor(Ares2D::Color4 color);
		void SetGradient(Ares2D::Color4 c1, Ares2D::Color4 c2, Ares2D::Color4 c3, Ares2D::Color4 c4);

		Ares2D::Float2 GetTranslation();
		void SetTranslation(Ares2D::Float2 translation);
		void Translate(Ares2D::Float2 translation);

		Ares2D::Float2 GetScale();
		void SetScale(Ares2D::Float2 scale);
		void Scale(Ares2D::Float2 scale);

		float GetAngle();
		void SetAngle(float angle);
		void Rotate(float angle);
	private:
		void SetVertices() override;
		void SetTransform() override;
	private:
		GEOMETRY_TYPE m_type = GEOMETRY_TYPE::RECT;
		
		// default values
		Ares2D::Float2 m_translation{ 0.0f, 0.0f };
		Ares2D::Float2 m_scale{ 1.0f, 1.0f };
		float m_angle = 0.0f;

		const static int m_sides = 4;

		// constructor
		Ares2D::Float2 m_position;
		Ares2D::Float2 m_size;
		Ares2D::Color4 m_color[m_sides];
		Ares2D::Float2 m_tex_cords[m_sides];
		float m_tex_id;
	};
};