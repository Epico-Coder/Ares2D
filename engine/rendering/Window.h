#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

class Window
{
public:
	Window(int width, int height, const char* title, bool vSync);
	~Window();

	void MakeContextCurrent();
	bool WindowOpen();

	void Clear(GLfloat r = 0, GLfloat g = 0, GLfloat b = 0, GLfloat a = 0);

	void SwapBuffers();
	void PollEvents();

	void Terminate();
private:
	GLFWwindow* m_Window;
};

