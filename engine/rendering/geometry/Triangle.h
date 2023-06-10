#pragma once

#include "engine/rendering/geometry/Geometry.h"
#include "engine/rendering/Renderer.h"

namespace Ares2D
{
	class Triangle : public Geometry
	{
		friend class Renderer;

	public:
		Triangle();

		// not right triangle
		Triangle(Ares2D::Float2 p1, Ares2D::Float2 p2, Ares2D::Float2 p3, Ares2D::Color4 color, TextureUse texture_use);
		Triangle(Ares2D::Float2 p1, Ares2D::Float2 p2, Ares2D::Float2 p3, Ares2D::Color4 color);
		Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);

		~Triangle();

		Ares2D::Float2 GetSize();
		void SetSize(Ares2D::Float2 size);

		Ares2D::Float2 GetPos();
		void SetPos(Ares2D::Float2 p1, Ares2D::Float2 p2, Ares2D::Float2 p3);

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
		void SetAngle(float angle, Ares2D::Float2 center);
		void Rotate(float angle);
		void Rotate(float angle, Ares2D::Float2 center);
	private:
		glm::vec2 RotateVertex(float x, float y, const glm::vec2& rotationPoint, const glm::mat2& rotationMatrix);
	private:
		GEOMETRY_TYPE m_type = GEOMETRY_TYPE::POINT;

		// set in constructor
		Ares2D::Float2 m_position[3];
		Ares2D::Color4 m_color;

		std::vector<float> m_og_vertices;

		// default values
		Ares2D::Float2 m_translation{ 0.0f, 0.0f };
		Ares2D::Float2 m_scale{ 1.0f, 1.0f };
		float m_angle = 0.0f;
	};
};