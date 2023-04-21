#pragma once

#include "dependancies/glfw/include/GLFW/glfw3.h"

#include <map>
#include <vector>
#include <string>

class Input {
public:
	Input();
	~Input();

	void Init(GLFWwindow* window);

	bool getIsKeyDown(int key);
	bool getisMouseButtonDown(int button);

	std::string getText() { return m_text; }
	void clearText() { m_text = ""; }

	std::vector<double> getMousePos() { return m_mouse_pos; }
	bool getCursorEntered() { return m_cursor_entered; }
	std::vector<double> getScrollOffset() { return m_scroll; }

	bool getIsEnabled() { return m_isEnabled; }
	void setIsEnabled(bool value) { m_isEnabled = value; }
private:
	static std::vector<Input*> m_instances;
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

	static void setupInputs(GLFWwindow* window);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void char_callback(GLFWwindow* window, unsigned int codepoint);
	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_enter_callback(GLFWwindow* window, int entered);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	
};

