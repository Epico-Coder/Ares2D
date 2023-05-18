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

void Window::SetCursorVisible()
{
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::SetCursorHidden()
{
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Window::SetCursorDefault()
{
    glfwSetCursor(m_Window, nullptr);
}

void Window::SetCursorImage(const std::string& filepath)
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

void Window::Terminate()
{
    glfwTerminate();
}
