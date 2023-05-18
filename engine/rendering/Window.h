#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

#include "dependancies/stbi_image/stb_image.h"

#include "engine/utils/color/Color.h"

#include <string>

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

	void SetCursorVisible();
	void SetCursorHidden();

	void SetCursorDefault();
	void SetCursorImage(const std::string& filepath);

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
