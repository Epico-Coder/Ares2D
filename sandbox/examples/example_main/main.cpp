#include <iostream>

#include "engine/Ares2D.h"

#include "dependancies/glm/glm.hpp"
#include "dependancies/glm/gtc/matrix_transform.hpp"

void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

void reDrawTileset(Renderer& renderer, Tileset& tileset)
{
    std::vector<std::vector<std::pair<unsigned int, unsigned int>>> tile_positions =
    {
        {{10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}},
        {{10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}},
        {{10, 04}, {10, 04}, {10, 04}, { 9, 02}, { 9, 03}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}},
        {{10, 04}, {10, 04}, {10, 04}, {10, 02}, {10, 03}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {03, 02}, {10, 04}},
        {{10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {04, 02}, {10, 04}},
        {{10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {03, 02}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {04, 02}, {10, 04}},
        {{10, 04}, {10, 04}, {10, 04}, {07, 06}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {05, 02}, {10, 04}, {10, 04}, {10, 04}, {10, 04}, {05, 03}, {10, 04}},
        {{00, 00}, {00, 01}, {00, 01}, {00, 01}, {00, 02}, {10, 04}, {04, 06}, {05, 06}, {10, 04}, {00, 00}, {00, 01}, {00, 01}, {00, 01}, {00, 01}, {00, 01}, {00, 02}, {00, 02}},
        {{01, 00}, {01, 01}, {01, 01}, {01, 01}, {01, 02}, {05, 05}, {05, 05}, {05, 05}, {05, 05}, {01, 00}, {01, 01}, {01, 01}, {01, 01}, {01, 01}, {01, 01}, {01, 01}, {01, 02}}
    };
    tileset.DrawTilePositions(renderer, 1280, 720, tile_positions);
}

int main()
{
    Ares2D::GLFWInit();

    Window win(1280, 720, "Abstracted window", true);
    win.MakeContextCurrent();

    Ares2D::GLEWInit();

    // Print OpenGL Version
    std::cout << Ares2D::GetVersion() << std::endl;

    // temp debug here
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    // Adding Entities into renderer
    // -> handle vertex inside
    Renderer renderer(500);
    
    Shader shader("engine/resources/shaders/shaders/VertexShader.shader", "engine/resources/shaders/shaders/FragmentShader.shader");
    shader.Bind();

    Input input(win.getWindow());

    Tileset tileset(shader, Ares2D::TEXTURE_HANDLER, "engine/resources/images/nature_tileset/nature-paltformer-tileset-16x16.png", 7, 11, 5);

    // Main Loop
    while (win.WindowOpen())
    {
        // Clearing vertices and indices(actually this time)
        win.Clear(0.0f, 153.0f, 219.0f);
        renderer.Clear();

        // Tileset drawing
        reDrawTileset(renderer, tileset);

        // Draw rect dynamically
        if (input.getisMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        {
            int size = 32.0f;
            
            float i = 0;
            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    Rect t_00(0.0f, 0.0f, size, size, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
                    t_00.Draw(renderer, float(input.getMousePos()[0] + (x * size)), float(input.getMousePos()[1] - (y * size)));
                    i++;
                }
            }
        }

        // Update Logic
        // -> renderer changes when geometry does
        renderer.Update();

        // Convert range of position vector from -1 to 1, to normal
        // -> Create math class
        glm::mat4 view = glm::ortho(0.0f, float(win.getWidth()), 0.0f, float(win.getHeight()), -1.0f, 1.0f);
        glm::mat4 mvp = view;
        shader.SetUniformMat4f("u_MVP", mvp);

        // Update ReDraw
        shader.Bind();

        renderer.Draw();

        // Swap back and front buffers
        win.SwapBuffers();
        // OS and User events
        win.PollEvents();
    }

    // Terminate after loop over
    win.Terminate();

    return 0;
}
