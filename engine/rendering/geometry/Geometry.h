#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "engine/utils/color/Color.h"
#include "engine/utils/math/Math.h"

#include <vector>


struct Vertex
{
	float Position[2];
	float mColor[4];
	float TexCords[2];
	float TexID;
	float TexIdx;
};

class Geometry
{
	friend class Renderer;
public:
	const static int vertex_num = 10;
	const static int vertex_size = sizeof(Vertex);

	virtual void Draw(Renderer& renderer, int x, int y) {}

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

