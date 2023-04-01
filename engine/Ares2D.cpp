#include "Ares2D.h"

unsigned int Ares2D::GLFWInit()
{
	if (glfwInit() != GLFW_TRUE)
		return ARES_FALSE;
	else
		return ARES_TRUE;
}

unsigned int Ares2D::GLEWInit()
{
	if (glewInit() != GLEW_OK)
		return ARES_FALSE;
	else
		return ARES_TRUE;
}

const GLubyte* Ares2D::GetVersion()
{
	return glGetString(GL_VERSION);

}