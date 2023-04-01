#include "Window.h"

Window::Window(int width, int height, const char* title, bool vSync)
{
	m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!m_Window)
        glfwTerminate();

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(vSync);
}

void Window::MakeContextCurrent()
{
    glfwMakeContextCurrent(m_Window);
}

bool Window::WindowOpen()
{
    return !glfwWindowShouldClose(m_Window);
}

void Window::Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::Terminate()
{
    glfwTerminate();
}

Window::~Window()
{  
}
