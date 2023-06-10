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
	const static int vertex_num = 9;
	const static int vertex_size = sizeof(Vertex);

	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;

	glm::mat4 m_transform;
};