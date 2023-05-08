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
#include "engine/rendering/storage/FrameBuffer.h"
#include "engine/rendering/storage/RenderBuffer.h"

#include "engine/rendering/geometry/Triangle.h"
#include "engine/rendering/geometry/Rect.h"
#include "engine/rendering/geometry/Circle.h"
#include "engine/rendering/geometry/Polygon.h"

#include "engine/resources/shaders/Shader.h"
#include "engine/resources/textures/Texture.h"

#include "engine/resources/resource/Resource.h"

#include "engine/utils/input/Input.h"
#include "engine/utils/ui/UI.h"
#include "engine/utils/math/Math.h"
#include "engine/utils/color/Color.h"


#include "engine/resources/vfx/VFX.h"

#include "engine/Control.h"

#include <Windows.h>

#define ARES_TRUE 1
#define ARES_FALSE 0
#define ARES_INVALID -1

#define ARES_KEY_LEFT GLFW_KEY_LEFT

#define ARES_NO_COLOR Color{0.0f, 0.0f, 0.0f, 0.0f}


namespace Ares2D
{   
    // Main
    static Window WINDOW;
    static Renderer RENDERER;
    static Input INPUT;

    // Rendering
    static AudioHandler AUDIO;
    static ShaderHandler SHADER;
    static TextureHandler TEXTURE(1000, 1000);
    static ResourceHandler RESOURCE;
    // static ImageHandler IMAGE;
    static VFXHandler VFX(&RENDERER, &TEXTURE);
     
    // Help
    static UI USER(&RENDERER);
    // static PhysicsHandler PHYSICS;
    // static Time CLOCK;
    // static Math MATH;

    static Control Init(int width, int height, const char* title)
    {
        if (!glfwInit())
            std::cout << "Error 1 while Initialization" << std::endl;
        if (!WINDOW.Init(width, height, title))
            std::cout << "Error 3 while Initialization" << std::endl;
        if (glewInit() != GLEW_OK)
            std::cout << "Error 2 while Initialization" << std::endl;

        RENDERER.Init(1000);
        INPUT.Init(WINDOW.GetWindow());
        TEXTURE.Init();

        return Control(&WINDOW, &RENDERER);
    }
}
