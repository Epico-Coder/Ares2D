#pragma once

#include "engine/rendering/geometry/Geometry.h"
#include "engine/rendering/Renderer.h"

namespace Ares2D
{
	class Point : public Geometry
	{
		friend class Renderer;

	public:
		Point();

		Point(Ares2D::Float2 position, Ares2D::Color4 color);
		Point(float x, float y, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);

		~Point();

		Ares2D::Float2 GetPos();
		void SetPos(Ares2D::Float2 pos);

		Ares2D::Color4 GetColor();
		void SetColor(Ares2D::Color4 color);

		Ares2D::Float2 GetTranslation();
		void SetTranslation(Ares2D::Float2 translation);
		void Translate(Ares2D::Float2 translation);
	private:
		GEOMETRY_TYPE m_type = GEOMETRY_TYPE::POINT;

		// set in constructor
		Ares2D::Float2 m_position;
		Ares2D::Color4 m_color;

		std::vector<float> m_og_vertices;

		// default values
		Ares2D::Float2 m_translation{ 0.0f, 0.0f };
		Ares2D::Float2 m_scale{ 1.0f, 1.0f };
		float m_angle = 0.0f;
	};
};

