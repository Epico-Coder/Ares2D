#include "Input.h"

#include <algorithm>

std::vector<KeyInput*> KeyInput::m_instances;

KeyInput::KeyInput(GLFWwindow* window, std::vector<int> keysToMonitor)
{
   m_isEnabled = true;

    for (int key : keysToMonitor) {
        m_keys[key] = false;
    }

    setupKeyInputs(window);

    KeyInput::m_instances.push_back(this);
}

KeyInput::~KeyInput() {
    m_instances.erase(std::remove(m_instances.begin(), m_instances.end(), this), m_instances.end());
}

bool KeyInput::getIsKeyDown(int key) {
    bool result = false;
    if (m_isEnabled) 
    {
        std::map<int, bool>::iterator it = m_keys.find(key);
        if (it != m_keys.end()) 
            result = m_keys[key];
        else
            m_keys.insert(std::make_pair(key, false));
    }
    return result;
}

void KeyInput::setIsKeyDown(int key, bool isDown) {
    std::map<int, bool>::iterator it = m_keys.find(key);
    if (it != m_keys.end()) {
        m_keys[key] = isDown;
    }
}

void KeyInput::setupKeyInputs(GLFWwindow* window) {
    glfwSetKeyCallback(window, KeyInput::callback);
}

void KeyInput::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (KeyInput* keyInput : m_instances) {
        keyInput->setIsKeyDown(key, action != GLFW_RELEASE);
    }
}