#include <iostream>

#include "engine/Ares2D.h"

using namespace Ares2D;

void reDrawTileset(Renderer& renderer)
{
    // TODO   
}

void reDraw(Renderer& renderer)
{
    // TODO
    reDrawTileset(renderer);
}

int main()
{

    /*-------------------------------------------------------------*/
    // Init

    const int WIDTH = 1280;
    const int HEIGHT = 720;
    Control ctrl = Init(WIDTH, HEIGHT, "Abstracted window");
    std::cout << ctrl.GetVersion() << std::endl;

    ctrl.EnableDebug();

    WIN.SetBlending(true);

    /*-------------------------------------------------------------*/
    // Audio

    AUDIO.add("sandbox/examples/example_main/audio/giorno.mp3", 1);
    //AUDIO.play(1);

    /*-------------------------------------------------------------*/
    // Adding single resource for nature tileset

    RESOURCE.AddResource("tileset", 960, 500);
    RESOURCE.AddShader("tileset", 1);

    TextureUse t_bg = RESOURCE.AddTexture("tileset", "engine/resources/images/nature_tileset/screenshot-1.png");
    Rect r_bg(Position{ 0.0f, 0.0f, WIDTH, HEIGHT - 100 }, ARES_NO_COLOR, t_bg);

    TextureUse t_grass = RESOURCE.AddTexture("tileset", "engine/resources/images/nature_tileset/tile000.png");
    Rect r_grass(Position{ 0.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, t_grass);

    TextureUse t_full = RESOURCE.FullTexture("tileset", 1);
    Rect r_full(Position{ 0.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, t_full);

    /*-------------------------------------------------------------*/
    // Fonts
    
    Rect square_red(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, Color{255.0f, 0.0f, 0.0f, 255.0f});

    Font boh(RESOURCE, "engine/utils/ui/fonts/boh.ttf", 24);

    /*-------------------------------------------------------------*/
    // Multiple effects

    ARES_VFX.AddVFX("1");

    /*-------------------------------------------------------------*/

    // Main Loop
    while (WIN.WindowOpen())
    {
        // Binds first Framebuffer
        ARES_VFX.Start();
        
        // Clearing vertices and indices(actually this time)
        WIN.Clear(Color{ 0.0f, 153.0f, 219.0f, 1.0f });
        RENDER.Clear();

        // Convert range of position vector from -1 to 1, to normal
        glm::mat4 view = glm::ortho(0.0f, float(WIN.getWidth()), 0.0f, float(WIN.getHeight()), -1.0f, 1.0f);
        glm::mat4 mvp = view;

        // Sets uniforms
        RESOURCE.BindResource("tileset", 1);
        RESOURCE.SetUniformMat4f("tileset", 1, "u_MVP", mvp);

        RESOURCE.BindResource("tileset", 1);
        r_bg.Add(RENDER);
        RENDER.Draw();

        // Render rects dynamically
        if (USERINPUT.getisMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        {   
            RESOURCE.BindResource("tileset", 1);
            r_grass.Add(RENDER, float(USERINPUT.getMousePos()[0]) - 75, float(USERINPUT.getMousePos()[1]) - 75);
            RENDER.Draw();
        }
        
        else if (USERINPUT.getisMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
        {
            ARES_VFX.Apply("1", EFFECT_EDGES, 0, 0, WIDTH, HEIGHT);
        }

        // Render text
        USER.RenderText(boh, "Right click: Effect", 50, 650, Color{ 0.98f, 0.52f, 0.26f, 1.0f }, 2);

        // Unbinds Framebuffer and draws screen wide rect
        ARES_VFX.End(RENDER);
        
        // Swap buffers and OS/User events
        WIN.Update();
    }

    // Terminate after loop over
    WIN.Terminate();

    return 0;
}
