#pragma once

#include "engine/includes.h"

struct Vertex
{
	float Position[2];
	float Color[4];
	float TexCords[2];
	float TexID;
};

class Renderable
{
public:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;

	glm::mat4 m_transform = glm::mat4(1.0);

	virtual void SetVertices() {}
	virtual void SetTransform() {}
};
