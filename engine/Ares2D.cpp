#include "Ares2D.h"

unsigned int Ares2D::Init()
{
	if ((glfwInit() != GLFW_TRUE) || (glewInit() != GLEW_OK))
		return ARES_FALSE;
	else
		return ARES_TRUE;
}

const GLubyte* Ares2D::GetVersion()
{
	return glGetString(GL_VERSION);

}