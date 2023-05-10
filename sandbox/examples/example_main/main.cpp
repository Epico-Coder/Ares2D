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
    const int WIDTH = 1280;
    const int HEIGHT = 720;
    Control ctrl = Init(WIDTH, HEIGHT, "Abstracted window");
    std::cout << ctrl.GetVersion() << std::endl;

    ctrl.EnableDebug();

    WIN.SetBlending(true);

    AUDIO.add("sandbox/examples/example_main/audio/giorno.mp3", 1);
    //AUDIO.play(1);

    //VFX.AddVFX("sandbox/examples/example_main/shaders/vfx/vfx.vert", "sandbox/examples/example_main/shaders/vfx/vfx.frag", 1);

    /*-------------------------------------------------------------*/

    RESOURCE.AddResource("grass", 64, 64);
    RESOURCE.AddShader("grass", "sandbox/examples/example_main/shaders/grass/vert_grass.shader", "sandbox/examples/example_main/shaders/grass/frag_grass.shader", 1);
    TextureUse tgrass_1 = RESOURCE.AddTexture("grass", "engine/resources/images/nature_tileset/tile000.png");
    TextureUse tgrass_2 = RESOURCE.AddTexture("grass", "engine/resources/images/nature_tileset/tile001.png");
    TextureUse tgrass_3 = RESOURCE.AddTexture("grass", "engine/resources/images/nature_tileset/tile002.png");
    TextureUse tgrass_4 = RESOURCE.AddTexture("grass", "engine/resources/images/nature_tileset/tile003.png");
    TextureUse tgrass_5 = RESOURCE.AddTexture("grass", "engine/resources/images/nature_tileset/tile004.png");
    TextureUse tgrass_f = RESOURCE.FullTexture("grass", tgrass_1.m_texture_id);

    Rect rgrass_1(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tgrass_1);
    Rect rgrass_2(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tgrass_2);
    Rect rgrass_3(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tgrass_3);
    Rect rgrass_4(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tgrass_4);
    Rect rgrass_5(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tgrass_5);
    Rect rgrass_f(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tgrass_f);

    /*-------------------------------------------------------------*/

    RESOURCE.AddResource("potion", 64, 64);
    RESOURCE.AddShader("potion", "sandbox/examples/example_main/shaders/potion/vert_potion.shader", "sandbox/examples/example_main/shaders/potion/frag_potion.shader", 1);
    TextureUse tpotion_1 = RESOURCE.AddTexture("potion", "engine/resources/images/nature_tileset/tile063.png");
    TextureUse tpotion_2 = RESOURCE.AddTexture("potion", "engine/resources/images/nature_tileset/tile064.png");
    TextureUse tpotion_3 = RESOURCE.AddTexture("potion", "engine/resources/images/nature_tileset/tile070.png");
    TextureUse tpotion_4 = RESOURCE.AddTexture("potion", "engine/resources/images/nature_tileset/tile071.png");
    TextureUse tpotion_f = RESOURCE.FullTexture("potion", tpotion_1.m_texture_id);

    Rect rpotion_1(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tpotion_1);
    Rect rpotion_2(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tpotion_2);
    Rect rpotion_3(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tpotion_3);
    Rect rpotion_4(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tpotion_4);
    Rect rpotion_f(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tpotion_f);

    /*-------------------------------------------------------------*/
    
    Rect square_red(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, Color{255.0f, 0.0f, 0.0f, 255.0f});

    Font arial(RESOURCE, "engine/utils/ui/fonts/arial.ttf", 48);
    Font boh(RESOURCE, "engine/utils/ui/fonts/boh.ttf", 48);

    TextureUse tfont_f = RESOURCE.FullTexture(USER.GetResourceID(), 1);
    Rect rfont_f(Position{ 100.0f, 0.0f, 150.0f, 150.0f }, ARES_NO_COLOR, tfont_f);

    // Main Loop
    while (WIN.WindowOpen())
    {
        // -> Nested VFXs
        //VFX.Start(1);
         
        /*-------------------------------------------------------------*/
        
        // Clearing vertices and indices(actually this time)
        WIN.Clear(Color{ 0.0f, 153.0f, 219.0f, 1.0f });
        RENDER.Clear();

        // Convert range of position vector from -1 to 1, to normal
        glm::mat4 view = glm::ortho(0.0f, float(WIN.getWidth()), 0.0f, float(WIN.getHeight()), -1.0f, 1.0f);
        glm::mat4 mvp = view;

        RESOURCE.BindResource("grass", 1);
        RESOURCE.SetUniformMat4f("grass", 1, "u_MVP", mvp);

        RESOURCE.BindResource("potion", 1);
        RESOURCE.SetUniformMat4f("potion", 1, "u_MVP", mvp);

        // Draw rect dynamically
        if (USERINPUT.getisMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        {   
            RESOURCE.BindResource("grass", 1);

            rgrass_1.Add(RENDER, float(USERINPUT.getMousePos()[0]), float(USERINPUT.getMousePos()[1]));

            RENDER.Draw();
        }
        
        else if (USERINPUT.getisMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
        {
            RESOURCE.BindResource("potion", 1);

            rpotion_1.Add(RENDER, float(USERINPUT.getMousePos()[0]), float(USERINPUT.getMousePos()[1]));

            RENDER.Draw();
        }

        USER.RenderText(arial, "Holy hell ! ! !\nnew line ?", 100, 250, Color{ 1.0f, 0.8f, 0.0f, 0.8f });
        USER.RenderText(boh, "Holy hell ! ! !\nnew line ?", 500, 250, Color{ 0.0f, 0.8f, 1.0f, 0.6f });

        /*-------------------------------------------------------------*/

        //VFX.End(1);
        
        // Swap buffers and OS/User events
        WIN.Update();
    }

    // Terminate after loop over
    WIN.Terminate();

    return 0;
}
