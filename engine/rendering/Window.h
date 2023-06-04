#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

#include "dependancies/stbi_image/stb_image.h"

#include "engine/utils/color/Color.h"

#include <string>

namespace Ares2D
{
	class Window
	{
	public:
		static Window& Instance();

		Window(Window const&) = delete;
		void operator=(Window const&) = delete;

		static bool Init(int width, int height, const char* title);
 		
		static void Update();

		static GLFWwindow* GetWindow();

		static void SetBlending(bool blending);

		static int getWidth();
		static int getHeight();

		static void SetCursorVisible();
		static void SetCursorHidden();

		static void SetCursorDefault();
		static void SetCursorImage(const std::string& filepath);

		static bool WindowOpen();

		static void Clear(Ares2D::Color4 color);

		static void SwapBuffers();
		static void PollEvents();
		static void Terminate();
	private:
		Window();
		~Window();
	private:
		bool i_Init(int width, int height, const char* title);

		void i_Update();

		GLFWwindow* i_GetWindow();

		void i_SetBlending(bool blending);

		int i_getWidth();
		int i_getHeight();

		void i_SetCursorVisible();
		void i_SetCursorHidden();

		void i_SetCursorDefault();
		void i_SetCursorImage(const std::string& filepath);

		bool i_WindowOpen();

		void i_Clear(Ares2D::Color4 color);

		void i_SwapBuffers();
		void i_PollEvents();
		void i_Terminate();
	private:
		GLFWwindow* m_Window;

		int m_width;
		int m_height;
	};
};