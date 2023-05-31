#include "Window.h"

#include <iostream>

namespace Ares2D
{
    Window::Window()
    {
    }

    Window::~Window()
    {
    }

    Window& Window::Instance()
    {
        static Window instance;
        return instance;
    }

    bool Window::Init(int width, int height, const char* title)
    {
        return Instance().i_Init(width, height, title);
    }

    void Window::Update()
    {
        Instance().i_Update();
    }

    GLFWwindow* Window::GetWindow()
    {
        return Instance().i_GetWindow();
    }

    void Window::SetBlending(bool blending)
    {
        Instance().i_SetBlending(blending);
    }

    bool Window::WindowOpen()
    {
        return Instance().i_WindowOpen();
    }

    void Window::Clear(Color color)
    {
        Instance().i_Clear(color);
    }

    void Window::SwapBuffers()
    {
        Instance().i_SwapBuffers();
    }

    void Window::PollEvents()
    {
        Instance().i_PollEvents();
    }

    int Window::getWidth()
    {
        return Instance().i_getWidth();
    }

    int Window::getHeight()
    {
        return Instance().i_getHeight();
    }

    void Window::SetCursorVisible()
    {
        Instance().i_SetCursorVisible();
    }

    void Window::SetCursorHidden()
    {
        Instance().i_SetCursorHidden();
    }

    void Window::SetCursorDefault()
    {
        Instance().i_SetCursorDefault();
    }

    void Window::SetCursorImage(const std::string& filepath)
    {
        Instance().i_SetCursorImage(filepath);
    }

    void Window::Terminate()
    {
        Instance().i_Terminate();
    }

    bool Window::i_Init(int width, int height, const char* title)
    {
        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        m_width = width;
        m_height = height;

        if (!m_Window)
        {
            std::cout << "no window" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1);

        glViewport(0, 0, width, height);

        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });

        glfwMakeContextCurrent(m_Window);

        return true;
    }

    void Window::i_Update()
    {
        SwapBuffers();
        PollEvents();
    }

    GLFWwindow* Window::i_GetWindow()
    {
        return m_Window;
    }

    void Window::i_SetBlending(bool blending)
    {
        if (blending)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else if (!blending)
        {
            glDisable(GL_BLEND);
        }
    }

    int Window::i_getWidth()
    {
        return m_width;
    }

    int Window::i_getHeight()
    {
        return m_height;
    }

    void Window::i_SetCursorVisible()
    {
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Window::i_SetCursorHidden()
    {
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void Window::i_SetCursorDefault()
    {
        glfwSetCursor(m_Window, nullptr);
    }

    void Window::i_SetCursorImage(const std::string& filepath)
    {
        int width, height, bpp;

        unsigned char* pixels = stbi_load(filepath.c_str(), &width, &height, &bpp, STBI_rgb_alpha);
        if (!pixels)
        {
            std::cout << "\nError: Failed to load cursor image: " << filepath << std::endl;
            std::cout << stbi_failure_reason() << std::endl;
            __debugbreak();
        }
        else
        {
            GLFWimage image;
            image.width = width;
            image.height = height;
            image.pixels = pixels;

            GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
            glfwSetCursor(m_Window, cursor);

            stbi_image_free(pixels);
        }
    }

    bool Window::i_WindowOpen()
    {
        return !glfwWindowShouldClose(m_Window);
    }

    void Window::i_Clear(Color color)
    {
        glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::i_SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }

    void Window::i_PollEvents()
    {
        glfwPollEvents();
    }

    void Window::i_Terminate()
    {
        glfwTerminate();
    }
};