#include <iostream>

#include "engine/Ares2D.h"

void reDrawTileset(Renderer& renderer)
{
    
}

void reDraw(Renderer& renderer)
{
    reDrawTileset(Ares2D::RENDERER);
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
    //Ares2D::SHADER.AddShader("sandbox/examples/example_main/vert.shader", "sandbox/examples/example_main/frag.shader", 2);

    Ares2D::USER.Init();

    //Tileset tileset(Ares2D::TEXTURENEW, "engine/resources/images/nature_tileset/nature-platformer-tileset-16x16.png", 7, 11, 5);

    Ares2D::AUDIO.add("sandbox/examples/example_main/sound_bg.mp3", 1);
    Ares2D::AUDIO.play(1);

    Ares2D::VFX.AddVFX("sandbox/examples/example_main/vert.shader", "sandbox/examples/example_main/frag1.shader", 1);

    // -> tile000 renders a texture, whereas tile001 breaks
    TextureUse texture_grass_1 = Ares2D::TEXTURE.AddTexture("engine/resources/images/nature_tileset/tile000.png");
    TextureUse texture_grass_2 = Ares2D::TEXTURE.AddTexture("engine/resources/images/nature_tileset/tile001.png");

    /*-------------------------------------------------------------*/
    
    Rect t_00(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, texture_grass_1);
    Rect t_01(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, texture_grass_2);

    // Main Loop
    while (Ares2D::WINDOW.WindowOpen())
    {
        // -> Nested VFXs
        Ares2D::VFX.Start(1);
         
        /*-------------------------------------------------------------*/
        
        // Clearing vertices and indices(actually this time)
        Ares2D::WINDOW.Clear(Color{ 0.0f, 153.0f, 219.0f, 1.0f });
        Ares2D::RENDERER.Clear();

        Ares2D::SHADER.BindShader(1);
        
        reDraw(Ares2D::RENDERER);

        // Draw rect dynamically
        if (Ares2D::INPUT.getisMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        {   
            t_00.Draw(Ares2D::RENDERER, float(Ares2D::INPUT.getMousePos()[0]), float(Ares2D::INPUT.getMousePos()[1]));
        }
        
        else if (Ares2D::INPUT.getisMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
        {
            t_01.Draw(Ares2D::RENDERER, float(Ares2D::INPUT.getMousePos()[0]), float(Ares2D::INPUT.getMousePos()[1]));

            // Set position to 14th second
            if (Ares2D::AUDIO.isPlaying(1))
                Ares2D::AUDIO.setTime(1, 14000);
        }

        // Convert range of position vector from -1 to 1, to normal
        glm::mat4 view = glm::ortho(0.0f, float(Ares2D::WINDOW.getWidth()), 0.0f, float(Ares2D::WINDOW.getHeight()), -1.0f, 1.0f);
        glm::mat4 mvp = view;
        Ares2D::SHADER.SetUniformMat4f(1, "u_MVP", mvp);

        // Update ReDraw
        Ares2D::RENDERER.Draw();
         
        /*-------------------------------------------------------------*/

        Ares2D::VFX.End(1);
        
        // Swap buffers and OS/User events
        Ares2D::WINDOW.Update();
        // Update Logic
        Ares2D::RENDERER.Update();
        
    }

    // Terminate after loop over
    Ares2D::WINDOW.Terminate();

    return 0;
}
