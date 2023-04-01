#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::DrawTestTriangle(float x, float y, float size) const
{
	glBegin(GL_TRIANGLES);
	glVertex2f(x - size, y);
	glVertex2f(x + size, y);
	glVertex2f(x,        y + (size * 2));
	glEnd();
}
