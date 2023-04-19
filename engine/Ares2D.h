#pragma once

#include <iostream>

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"
#include "dependancies/glm/glm.hpp"
#include "dependancies/glm/gtc/matrix_transform.hpp"

#include "engine/rendering/Window.h"
#include "engine/rendering/Renderer.h"
#include "engine/resources/audio/Audio.h"

#include "engine/rendering/storage/VertexBuffer.h"
#include "engine/rendering/storage/VertexBufferLayout.h"
#include "engine/rendering/storage/VertexArray.h"
#include "engine/rendering/storage/IndexBuffer.h"

#include "engine/rendering/geometry/Triangle.h"
#include "engine/rendering/geometry/Rect.h"
#include "engine/rendering/geometry/Circle.h"
#include "engine/rendering/geometry/Polygon.h"

#include "engine/resources/shaders/Shader.h"

#include "engine/resources/textures/Texture.h"
#include "engine/resources/tilesets/Tileset.h"

#include "engine/utils/input/Input.h"
#include "engine/utils/ui/UI.h"

#include <Windows.h>

#define ARES_TRUE 1
#define ARES_FALSE 0

#define ARES_KEY_LEFT GLFW_KEY_LEFT

namespace Ares2D
{
    unsigned int GLFWInit();
    unsigned int GLEWInit();
    
    const GLubyte* GetVersion();

    // static Window ARES_WINDOW;
    // static Renderer ARES_RENDERER;
    // static Input ARES_INPUT;

    // static UI ARES_UI;

    static AudioHandler ARES_AUDIO_HANDLER;

    // static ImageHandler ARES_IMAGE_HANDLER;
    // static ShaderHandler ARES_SHADER_HANDLER
    static TextureHandler ARES_TEXTURE_HANDLER;
}
