#include "Input.h"

#include <algorithm>

std::vector<InputHandler*> InputHandler::m_instances;

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler() {
    m_instances.erase(std::remove(m_instances.begin(), m_instances.end(), this), m_instances.end());
}

void InputHandler::Init(GLFWwindow* window)
{
    m_isEnabled = true;

    m_text = "";
    m_mouse_pos = { 0, 0 };
    m_cursor_entered = false;
    m_scroll = { 0, 0 };

    setupInputs(window);
    InputHandler::m_instances.push_back(this);
}

bool InputHandler::getIsKeyDown(int key) {
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

bool InputHandler::getisMouseButtonDown(int button)
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

void InputHandler::setIsKeyDown(int key, bool isDown) {
    std::map<int, bool>::iterator it = m_keys.find(key);
    if (it != m_keys.end()) {
        m_keys[key] = isDown;
    }
}

void InputHandler::setIsMouseButtonDown(int button, bool isDown) {
    std::map<int, bool>::iterator it = m_mouse.find(button);
    if (it != m_mouse.end()) {
        m_mouse[button] = isDown;
    }
}

void InputHandler::setupInputs(GLFWwindow* window) 
{
    glfwSetKeyCallback(window, InputHandler::key_callback);
    glfwSetCharCallback(window, InputHandler::char_callback);
    glfwSetCursorPosCallback(window, InputHandler::cursor_pos_callback);
    glfwSetMouseButtonCallback(window, InputHandler::mouse_button_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    for (InputHandler* InputHandler : m_instances) 
    {
        InputHandler->setIsKeyDown(key, action != GLFW_RELEASE);
    }
}

void InputHandler::char_callback(GLFWwindow* window, unsigned int codepoint)
{
    for (InputHandler* InputHandler : m_instances) 
    {
        InputHandler->m_text += codepoint;
    }
}

void InputHandler::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    int height;
    glfwGetWindowSize(window, nullptr, &height);
    for (InputHandler* InputHandler : m_instances) 
    {
        InputHandler->m_mouse_pos[0] = xpos;
        InputHandler->m_mouse_pos[1] = height - ypos;
    }
}

void InputHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    for (InputHandler* InputHandler : m_instances) 
    {
        InputHandler->setIsMouseButtonDown(button, action != GLFW_RELEASE);
    }
}

void InputHandler::cursor_enter_callback(GLFWwindow* window, int entered)
{
    for (InputHandler* InputHandler : m_instances) 
    {
        InputHandler->m_cursor_entered = entered;
    }
}

void InputHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    for (InputHandler* InputHandler : m_instances) 
    {
        InputHandler->m_scroll[0] = xoffset;
        InputHandler->m_scroll[1] = yoffset;
    }
}
