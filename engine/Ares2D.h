#pragma once

#include "engine/rendering/Window.h"
#include "engine/rendering/Renderer.h"

#include "engine/resources/audio/Audio.h"
#include "engine/resources/vfx/VFX.h"

#include "engine/utils/ui/UI.h"

#include "engine/rendering/geometry/Rect.h"
#include "engine/rendering/geometry/Triangle.h"

#include <iostream>

#define ARES_TRUE 1
#define ARES_FALSE 0
#define ARES_INVALID -1

#define ARES_KEY_LEFT GLFW_KEY_LEFT

#define ARES_NO_COLOR Ares2D::Color4{0.0f, 0.0f, 0.0f, 0.0f}


namespace Ares2D
{
    static void Init(int width, int height, const char* title)
    {
        if (!glfwInit())
        {
            std::cout << "GLFW not initialized!" << std::endl;
        }
        if (Ares2D::Window::Init(width, height, title) == ARES_FALSE)
        {
            std::cout << "Window not initialized!" << std::endl;
        }
        if (glewInit() != GLEW_OK)
        {
            std::cout << "GLEW not initialized!" << std::endl;
        }
       
        Ares2D::Renderer::Init(10000);
        Ares2D::UI::Init();
    }
};
