#include <iostream>

#include "engine/Ares2D.h"

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
        {{00, 00}, {00, 01}, {00, 01}, {00, 01}, {00, 02}, {10, 04}, {04, 06}, {05, 06}, {10, 04}, {00, 00}, {00, 01}, {00, 01}, {00, 01}, {00, 01}, {00, 01}, {00, 01}, {00, 02}},
        {{01, 00}, {01, 01}, {01, 01}, {01, 01}, {01, 02}, {05, 05}, {05, 05}, {05, 05}, {05, 05}, {01, 00}, {01, 01}, {01, 01}, {01, 01}, {01, 01}, {01, 01}, {01, 01}, {01, 02}}
    };
    tileset.DrawTilePositions(renderer, 1280, 720, tile_positions);
}

int main()
{
    const int WIDTH = 1280;
    const int HEIGHT = 720;
    Control ctrl = Ares2D::Init(WIDTH, HEIGHT, "Abstracted window");
    std::cout << ctrl.GetVersion() << std::endl;

    ctrl.EnableDebug();

    Ares2D::WINDOW.SetBlending(true);

    // Adding Entities into renderer
    
    Ares2D::SHADER.AddShader("engine/resources/shaders/shaders/VertexShader.shader", "engine/resources/shaders/shaders/FragmentShader.shader", 1);
    Ares2D::SHADER.AddShader("sandbox/examples/example_main/vert.shader", "sandbox/examples/example_main/frag.shader", 2);

    Ares2D::USER.Init();

    Tileset tileset(Ares2D::TEXTURE, "engine/resources/images/nature_tileset/nature-platformer-tileset-16x16.png", 7, 11, 5);
    
    Ares2D::AUDIO.add("sandbox/examples/example_main/sound_bg.mp3", 1);
    Ares2D::AUDIO.play(1);
        
    /*-------------------------------------------------------------*/
    float quadVertices[] = {
            -1.0f,  1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
             1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f,  1.0f, 0.0f, 1.0f,
             1.0f, -1.0f, 1.0f, 0.0f,
             1.0f,  1.0f, 1.0f, 1.0f
    };

    VertexBuffer vbo(&quadVertices, sizeof(quadVertices));
    VertexArray vao;
    vao.Bind();
    VertexBufferLayout vbl;
    vbl.Push<GLfloat>(2);
    vbl.Push<GLfloat>(2);
    vao.AddBuffer(vbo, vbl);

    FrameBuffer fbo;
    Texture texture(WIDTH, HEIGHT);
    RenderBuffer rbo;
    rbo.Bind();
    rbo.storage(GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);

    fbo.Bind();
    fbo.AttachTexture2D(texture, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0);
    fbo.AttachRenderBuffer(rbo, GL_DEPTH_STENCIL_ATTACHMENT);

    // Main Loop
    while (Ares2D::WINDOW.WindowOpen())
    {
        fbo.Bind();
        texture.Unbind();
         
        /*-------------------------------------------------------------*/

        // Clearing vertices and indices(actually this time)
        Ares2D::WINDOW.Clear(Color{ 0.0f, 153.0f, 219.0f, 1.0f });
        Ares2D::RENDERER.Clear();

        Ares2D::SHADER.BindShader(1);
                
        reDrawTileset(Ares2D::RENDERER, tileset);

        // Draw rect dynamically
        if (Ares2D::INPUT.getisMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        {
            int size = 32.0f;
            
            Rect t_00(0.0f, 0.0f, size, size, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
            t_00.Draw(Ares2D::RENDERER, float(Ares2D::INPUT.getMousePos()[0]), float(Ares2D::INPUT.getMousePos()[1]));
        }

        if (Ares2D::INPUT.getisMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
        {
            // Set position to 14th second
            if (Ares2D::AUDIO.isPlaying(1))
                Ares2D::AUDIO.setTime(1, 14000);
        }

        // Convert range of position vector from -1 to 1, to normal
        // -> Create math class
        glm::mat4 view = glm::ortho(0.0f, float(Ares2D::WINDOW.getWidth()), 0.0f, float(Ares2D::WINDOW.getHeight()), -1.0f, 1.0f);
        glm::mat4 mvp = view;
        Ares2D::SHADER.SetUniformMat4f(1, "u_MVP", mvp);

        // Update ReDraw
        Ares2D::RENDERER.Draw();

        // Will not work as clear color blocks it or something idk
        Ares2D::USER.RenderText("Ui", 300.0f, 550.0f, 1.0f, glm::vec3(0.0f, 1.0f, 1.0f));
        Ares2D::USER.RenderText("hello", 300.0f, 600.0f, 1.0f, glm::vec3(0.95f, 0.7f, 0.05f));

        /*-------------------------------------------------------------*/
        Ares2D::SHADER.BindShader(2);

        fbo.Unbind();

        Ares2D::WINDOW.Clear(Color{ 0.0f, 0.0f, 0.0f, 1.0f });

        vao.Bind();
        texture.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // Swap back and front buffers
        // OS and User events
        Ares2D::WINDOW.Update();
        // Update Logic
        Ares2D::RENDERER.Update();
    }

    // Terminate after loop over
    Ares2D::WINDOW.Terminate();

    return 0;
}
