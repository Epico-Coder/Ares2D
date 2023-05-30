#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

#include "engine/rendering/Window.h"

#include <map>
#include <vector>
#include <string>

namespace Ares2D
{
	class Input {
	public:
		static Input& Instance();

		Input(Input const&) = delete;
		void operator=(Input const&) = delete;

		static bool getIsKeyDown(int key);

		static bool getIsMouseButtonDown(int button);

		static std::string getText();
		static void clearText();

		static std::vector<double> getMousePos();
		static bool getCursorEntered();
		static std::vector<double> getScrollOffset();

	private:
		Input();
		~Input();

	private:
		bool i_getIsKeyDown(int key);

		bool i_getIsMouseButtonDown(int button);

		std::string i_getText();
		void i_clearText();

		std::vector<double> i_getMousePos();
		bool i_getCursorEntered();
		std::vector<double> i_getScrollOffset();

	private:
		bool m_isEnabled;

		std::map<int, bool> m_keys;
		std::map<int, bool> m_mouse;

		std::string m_text;
		std::vector<double> m_mouse_pos;
		bool m_cursor_entered;
		std::vector<double> m_scroll;

	private:
		void setIsKeyDown(int key, bool isDown);
		void setIsMouseButtonDown(int button, bool isDown);

		static void setupInputs();

		static void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
		static void char_callback(GLFWwindow*, unsigned int codepoint);
		static void cursor_pos_callback(GLFWwindow*, double xpos, double ypos);
		static void mouse_button_callback(GLFWwindow*, int button, int action, int mods);
		static void cursor_enter_callback(GLFWwindow*, int entered);
		static void scroll_callback(GLFWwindow*, double xoffset, double yoffset);
	};
};
