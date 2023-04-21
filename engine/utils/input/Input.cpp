#include "Input.h"

#include <algorithm>

std::vector<Input*> Input::m_instances;

Input::Input(GLFWwindow* window, std::vector<int> keysToMonitor)
{
    m_isEnabled = true;

    for (int key : keysToMonitor)
        m_keys[key] = false;

    m_text = "";
    m_mouse_pos = { 0, 0 };
    m_cursor_entered = false;
    m_scroll = { 0, 0 };

    setupInputs(window);
    Input::m_instances.push_back(this);
}

Input::~Input() {
    m_instances.erase(std::remove(m_instances.begin(), m_instances.end(), this), m_instances.end());
}

bool Input::getIsKeyDown(int key) {
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

bool Input::getisMouseButtonDown(int button)
{
    bool result = false;
    if (m_isEnabled)
    {
        std::map<int, bool>::iterator it = m_mouse.find(button);
        if (it != m_mouse.end())
            result = m_mouse[button];
        else
            m_mouse.insert(std::make_pair(button, false));
    }
    return result;
}

void Input::setIsKeyDown(int key, bool isDown) {
    std::map<int, bool>::iterator it = m_keys.find(key);
    if (it != m_keys.end()) {
        m_keys[key] = isDown;
    }
}

void Input::setIsMouseButtonDown(int button, bool isDown) {
    std::map<int, bool>::iterator it = m_mouse.find(button);
    if (it != m_mouse.end()) {
        m_mouse[button] = isDown;
    }
}

void Input::setupInputs(GLFWwindow* window) 
{
    glfwSetKeyCallback(window, Input::key_callback);
    glfwSetCharCallback(window, Input::char_callback);
    glfwSetCursorPosCallback(window, Input::cursor_pos_callback);
    glfwSetMouseButtonCallback(window, Input::mouse_button_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    for (Input* Input : m_instances) 
    {
        Input->setIsKeyDown(key, action != GLFW_RELEASE);
    }
}

void Input::char_callback(GLFWwindow* window, unsigned int codepoint)
{
    for (Input* Input : m_instances) 
    {
        Input->m_text += codepoint;
    }
}

void Input::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    int height;
    glfwGetWindowSize(window, nullptr, &height);
    for (Input* Input : m_instances) 
    {
        Input->m_mouse_pos[0] = xpos;
        Input->m_mouse_pos[1] = height - ypos;
    }
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    for (Input* Input : m_instances) 
    {
        Input->setIsMouseButtonDown(button, action != GLFW_RELEASE);
    }
}

void Input::cursor_enter_callback(GLFWwindow* window, int entered)
{
    for (Input* Input : m_instances) 
    {
        Input->m_cursor_entered = entered;
    }
}

void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    for (Input* Input : m_instances) 
    {
        Input->m_scroll[0] = xoffset;
        Input->m_scroll[1] = yoffset;
    }
}
