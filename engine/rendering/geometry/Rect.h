#pragma once

#include "engine/rendering/geometry/Geometry.h"
#include "engine/rendering/Renderer.h"

class Rect : public Geometry
{
	friend class Renderer;

public:
	Rect();

	Rect(Ares2D::Float4 position, Ares2D::Color4 color, TextureUse texture_use);
	Rect(Ares2D::Float4 position, Ares2D::Color4 color);
	Rect(float x, float y, float width, float height, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);

	~Rect();

	Ares2D::Float4 GetRect();

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
	void SetAngle(float angle, Ares2D::Float2 center);
	void Rotate(float angle);
	void Rotate(float angle, Ares2D::Float2 center);
private:
	glm::vec2 RotateVertex(float x, float y, const glm::vec2& rotationPoint, const glm::mat2& rotationMatrix);
private:
	// set in constructor
	Ares2D::Float4 m_position;
	Ares2D::Color4 m_color;

	std::vector<float> m_og_vertices;

	// default values
	Ares2D::Float2 m_translation{0.0f, 0.0f};
	Ares2D::Float2 m_scale{1.0f, 1.0f};
	float m_angle = 0.0f;
};

