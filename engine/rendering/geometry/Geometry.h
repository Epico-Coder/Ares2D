#pragma once

#include <vector>

#include "dependancies/glew/include/GL/glew.h"
#include "engine/utils/color/Color.h"

struct Vertex
{
	float Position[2];
	float mColor[4];
	float TexCords[2];
	float TexID;
};

class Geometry
{
	friend class Renderer;

public:
	virtual void SetColor(Color color) {}
	virtual void SetGradient(Color color) {}

	virtual void Translate(float x, float y) {}
	virtual void Scale(float x, float y) {}
	virtual void Rotate(float angle) {}
protected:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
private:
	int m_sides;
};

