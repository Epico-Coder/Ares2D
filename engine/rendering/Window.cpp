#include "Window.h"

Window::Window(int width, int height, const char* title, bool vSync)
{
	m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    m_width = width;
    m_height = height;

    if (!m_Window)
        glfwTerminate();

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    glViewport(0, 0, width, height);
    
    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);
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

GLFWwindow* Window::getWindow()
{
    return m_Window;
}

Window::~Window()
{
}

