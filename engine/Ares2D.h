#pragma once

#include <iostream>

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"

#include "engine/rendering/Window.h"
#include "engine/rendering/Renderer.h"

#include "engine/rendering/storage/VertexBuffer.h"
#include "engine/rendering/storage/VertexBufferLayout.h"
#include "engine/rendering/storage/VertexArray.h"
#include "engine/rendering/storage/IndexBuffer.h"

#include "engine/rendering/geometry/Triangle.h"
#include "engine/rendering/geometry/Rect.h"
#include "engine/rendering/geometry/Circle.h"
#include "engine/rendering/geometry/Polygon.h"

#include "engine/resources/shaders/Shader.h"

#include "engine/utils/input/Input.h"

#define ASSERT(x) if (!(x)) __debugbreak();

#define ARES_TRUE 1
#define ARES_FALSE 0


#define ARES_KEY_LEFT GLFW_KEY_LEFT


namespace Ares2D
{
    unsigned int GLFWInit();
    unsigned int GLEWInit();
    
    const GLubyte* GetVersion();

}
