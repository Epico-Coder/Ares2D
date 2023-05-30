#include "Input.h"

#include <algorithm>

namespace Ares2D
{

    /*-------------------------- Public Functions --------------------------*/

    Input::Input()
        : m_isEnabled(true), m_text(""), m_mouse_pos({0, 0}), m_cursor_entered(false), m_scroll({0, 0})
    {
        setupInputs();
    }

    Input::~Input() 
    {
    }

    Input& Input::Instance()
    {
        static Input instance;
        return instance;
    }

    bool Input::getIsKeyDown(int key)
    {
        return Instance().i_getIsKeyDown(key);
    }

    bool Input::getIsMouseButtonDown(int button)
    {
        return Instance().i_getIsMouseButtonDown(button);
    }

    std::string Input::getText()
    {
        return Instance().i_getText();
    }

    void Input::clearText()
    {
        Instance().clearText();
    }

    std::vector<double> Input::getMousePos()
    {
        return Instance().i_getMousePos();
    }

    bool Input::getCursorEntered()
    {
        return Instance().i_getCursorEntered();
    }

    std::vector<double> Input::getScrollOffset()
    {
        return Instance().i_getScrollOffset();
    }

    /*-------------------------- Internal Functions --------------------------*/

    bool Input::i_getIsKeyDown(int key)
    {
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

    bool Input::i_getIsMouseButtonDown(int button)
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

    std::string Input::i_getText()
    {
        return m_text;
    }

    void Input::i_clearText()
    {
        m_text.clear();
    }

    std::vector<double> Input::i_getMousePos()
    {
        return m_mouse_pos;
    }

    bool Input::i_getCursorEntered()
    {
        return m_cursor_entered;
    }

    std::vector<double> Input::i_getScrollOffset()
    {
        return m_scroll;
    }

    /*-------------------------- Private Functions --------------------------*/

    void Input::setIsKeyDown(int key, bool isDown)
    {
        std::map<int, bool>::iterator it = m_keys.find(key);
        if (it != m_keys.end())
        {
            m_keys[key] = isDown;
        }
    }
    
    void Input::setIsMouseButtonDown(int button, bool isDown)
    {
        std::map<int, bool>::iterator it = m_mouse.find(button);
        if (it != m_mouse.end())
        {
            m_mouse[button] = isDown;
        }
    }

    void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Instance().setIsKeyDown(key, action != GLFW_RELEASE);
    }

    void Input::char_callback(GLFWwindow*, unsigned int codepoint)
    {
        Instance().m_text += codepoint;
    }

    void Input::cursor_pos_callback(GLFWwindow*, double xpos, double ypos)
    {
        Instance().m_mouse_pos[0] = xpos;
        // invert the y-cord
        Instance().m_mouse_pos[1] = Ares2D::Window::getHeight() - ypos;
    }

    void Input::mouse_button_callback(GLFWwindow*, int button, int action, int mods)
    {
        Instance().setIsMouseButtonDown(button, action != GLFW_RELEASE);
    }

    void Input::cursor_enter_callback(GLFWwindow*, int entered)
    {
        Instance().m_cursor_entered = entered;
    }

    void Input::scroll_callback(GLFWwindow*, double xoffset, double yoffset)
    {
        Instance().m_scroll[0] = xoffset;
        Instance().m_scroll[1] = yoffset;
    }

    void Input::setupInputs()
    {
        // set inputs only for main window
        glfwSetKeyCallback(Ares2D::Window::GetWindow(), key_callback);
        glfwSetCharCallback(Ares2D::Window::GetWindow(), char_callback);
        glfwSetCursorPosCallback(Ares2D::Window::GetWindow(), cursor_pos_callback);
        glfwSetMouseButtonCallback(Ares2D::Window::GetWindow(), mouse_button_callback);
        glfwSetCursorEnterCallback(Ares2D::Window::GetWindow(), cursor_enter_callback);
        glfwSetScrollCallback(Ares2D::Window::GetWindow(), scroll_callback);
    }
};