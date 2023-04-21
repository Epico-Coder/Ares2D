#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"
#include "engine/utils/color/Color.h"

class Window
{
public:
	Window();
	~Window();

	bool Init(int width, int height, const char* title);

	void Update();

	GLFWwindow* GetWindow();

	void SetBlending(bool blending);

	int getWidth();
	int getHeight();

	bool WindowOpen();

	void Clear(Color color);

	void SwapBuffers();
	void PollEvents();
	void Terminate();
private:
	GLFWwindow* m_Window;

	int m_width;
	int m_height;
};
