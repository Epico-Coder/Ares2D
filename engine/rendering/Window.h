#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

class Window
{
public:
	Window(int width, int height, const char* title, bool vSync);
	~Window();

	GLFWwindow* getWindow();

	int getWidth();
	int getHeight();

	void MakeContextCurrent();
	bool WindowOpen();

	void Clear(GLfloat r = 50.0f, GLfloat g = 50.0f, GLfloat b = 50.0f, GLfloat a = 255.0f);

	void SwapBuffers();

	void PollEvents();

	void Terminate();
private:
	GLFWwindow* m_Window;

	int m_width;
	int m_height;
};
