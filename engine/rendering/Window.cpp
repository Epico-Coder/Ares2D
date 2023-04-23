#include "Window.h"
#include <iostream>

Window::Window()
{   
}

Window::~Window()
{
}

bool Window::Init(int width, int height, const char* title)
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

void Window::Update()
{
    SwapBuffers();
    PollEvents();
}

GLFWwindow* Window::GetWindow()
{
    return m_Window;
}

void Window::SetBlending(bool blending)
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

bool Window::WindowOpen()
{
    return !glfwWindowShouldClose(m_Window);
}

void Window::Clear(Color color)
{
    glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

int Window::getWidth()
{
    return m_width;
}

int Window::getHeight()
{
    return m_height;
}

void Window::Terminate()
{
    glfwTerminate();
}
