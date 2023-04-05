#pragma once

#include "dependancies/glfw/include/GLFW/glfw3.h"

#include <map>
#include <vector>

class Input
{
};

class KeyInput {
public:
	KeyInput(GLFWwindow* window, std::vector<int> keysToMonitor={});
	~KeyInput();
	bool getIsKeyDown(int key);
	bool getIsEnabled() { return m_isEnabled; }
	void setIsEnabled(bool value) { m_isEnabled = value; }

private:
	static std::vector<KeyInput*> m_instances;
	std::map<int, bool> m_keys;
	bool m_isEnabled;

private:
	void setIsKeyDown(int key, bool isDown);
	static void setupKeyInputs(GLFWwindow* window);
	static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

