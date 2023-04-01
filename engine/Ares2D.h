#pragma once

#include <iostream>

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

#include "engine/rendering/Window.h"
#include "engine/rendering/Renderer.h"

#include "engine/resources/shaders/Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();

#define ARES_TRUE 1
#define ARES_FALSE 0

namespace Ares2D
{
    unsigned int Init();
    
    const GLubyte* GetVersion();

}
