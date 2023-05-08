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
    //Ares2D::AUDIO.play(1);

    //Ares2D::VFX.AddVFX("sandbox/examples/example_main/vert.shader", "sandbox/examples/example_main/frag1.shader", 1);

    // -> tile000 renders a texture, whereas tile001 breaks

    TextureUse texture_grass_1 = Ares2D::TEXTURE.AddTexture("engine/resources/images/nature_tileset/tile000.png");
    TextureUse texture_grass_2 = Ares2D::TEXTURE.AddTexture("engine/resources/images/nature_tileset/tile001.png");
    TextureUse texture_grass_3 = Ares2D::TEXTURE.AddTexture("engine/resources/images/nature_tileset/tile002.png");
    TextureUse texture_grass_4 = Ares2D::TEXTURE.AddTexture("engine/resources/images/nature_tileset/tile003.png");
    TextureUse texture_grass_5 = Ares2D::TEXTURE.AddTexture("engine/resources/images/nature_tileset/tile004.png");
    TextureUse texture_grass_6 = Ares2D::TEXTURE.AddTexture("engine/resources/images/nature_tileset/tile005.png");
    TextureUse texture_grass_7 = Ares2D::TEXTURE.AddTexture("engine/resources/images/nature_tileset/tile006.png");
    TextureUse texture_grass_8 = Ares2D::TEXTURE.AddTexture("engine/resources/images/nature_tileset/tile007.png");
    TextureUse texture_grass_9 = Ares2D::TEXTURE.AddTexture("engine/resources/images/nature_tileset/tile008.png");

    TextureUse texture_full_1 = Ares2D::TEXTURE.FullTexture(1);
    TextureUse texture_full_2 = Ares2D::TEXTURE.FullTexture(2);
    /*-------------------------------------------------------------*/
    
    Rect square_red(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, Color{255.0f, 0.0f, 0.0f, 255.0f});
    Rect grass_1(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, texture_grass_1);

    Rect full_tex_1(Position{ 100.0f, 100.0f, 500.0f, 1000.0f }, ARES_NO_COLOR, texture_full_1);
    Rect full_tex_2(Position{ 100.0f, 100.0f, 500.0f, 1000.0f }, ARES_NO_COLOR, texture_full_2);

    Font arial(Ares2D::TEXTURE, "engine/utils/ui/fonts/arial.ttf", 48);
    Font boh(Ares2D::TEXTURE, "engine/utils/ui/fonts/boh.ttf", 48);

    // Main Loop
    while (Ares2D::WINDOW.WindowOpen())
    {
        // -> Nested VFXs
        //Ares2D::VFX.Start(1);
         
        /*-------------------------------------------------------------*/
        
        // Clearing vertices and indices(actually this time)
        Ares2D::WINDOW.Clear(Color{ 0.0f, 153.0f, 219.0f, 1.0f });
        Ares2D::RENDERER.Clear();

        Ares2D::SHADER.BindShader(1);
        reDraw(Ares2D::RENDERER);

        // Draw rect dynamically
        if (Ares2D::INPUT.getisMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        {   
            full_tex_1.Draw(Ares2D::RENDERER, float(Ares2D::INPUT.getMousePos()[0]), float(Ares2D::INPUT.getMousePos()[1]));
        }
        
        else if (Ares2D::INPUT.getisMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
        {
            grass_1.Draw(Ares2D::RENDERER, float(Ares2D::INPUT.getMousePos()[0]), float(Ares2D::INPUT.getMousePos()[1]));
        }

        // Convert range of position vector from -1 to 1, to normal
        glm::mat4 view = glm::ortho(0.0f, float(Ares2D::WINDOW.getWidth()), 0.0f, float(Ares2D::WINDOW.getHeight()), -1.0f, 1.0f);
        glm::mat4 mvp = view;
        Ares2D::SHADER.SetUniformMat4f(1, "u_MVP", mvp);

        Ares2D::USER.RenderText(Ares2D::RENDERER, arial, "Holy hell ! ! !\nnew line ?", 100, 250, Color{ 1.0f, 0.8f, 0.0f, 0.8f });
        Ares2D::USER.RenderText(Ares2D::RENDERER, boh, "Holy hell ! ! !\nnew line ?", 500, 250, Color{ 0.0f, 0.8f, 1.0f, 0.8f });

        // Update ReDraw
        Ares2D::RENDERER.Draw();
         
        /*-------------------------------------------------------------*/

        //Ares2D::VFX.End(1);
        
        // Swap buffers and OS/User events
        Ares2D::WINDOW.Update();
        // Update Logic
        Ares2D::RENDERER.Update();
        
    }

    // Terminate after loop over
    Ares2D::WINDOW.Terminate();

    return 0;
}
