#pragma once

#include "engine/rendering/geometry/Geometry.h"
#include "engine/rendering/Renderer.h"

class Rect : public Geometry
{
	friend class Renderer;

public:
	Rect();
	Rect(Position position, Color color, TextureUse texture_use);
	Rect(Position position, Color color, float TexID = 0.0f);
	Rect(float x, float y, float width, float height, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f, float TexID = 0.0f);
	Rect(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
	~Rect();

	void Add(Renderer& renderer);
	void Add(Renderer& renderer, int x, int y);

	Position GetPos();
	void SetPos(int x, int y);

	void SetColor(Color color);
	void SetGradient(Color c1, Color c2, Color c3, Color c4);
	void SetTexCords(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	void SetTexID(unsigned int TexID);

	glm::mat4 getModel();

	void Translate(float x, float y);
	void Scale(float x, float y) {}
	void Rotate(float angle) {}

private:
	glm::mat4 m_Model = glm::mat4(1.0f);

	Position m_position;

	int m_width;
	int m_height;
};

