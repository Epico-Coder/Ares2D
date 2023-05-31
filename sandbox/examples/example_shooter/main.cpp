#include "engine/Ares2D.h"

#include <algorithm>

#include <windows.h>
#include <psapi.h>
#include <iostream>

float DisplayMemoryInfo()
{
    HANDLE hProcess = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    CloseHandle(hProcess);

    // in mb
    return pmc.PrivateUsage / 1048576;
}


int main()
{
    /*-------------------------------------------------------------*/
    // Init

    const int WIDTH = 1280;
    const int HEIGHT = 720;

    Ares2D::Init(WIDTH, HEIGHT, "Abstracted window");

    Ares2D::Window::SetBlending(true);
    Ares2D::Window::SetCursorImage("sandbox/examples/example_shooter/images/crosshairs/Outline/CrosshairsOutline01.png");


    /*-------------------------------------------------------------*/
    // Resources

    Ares2D::Resource::AddResource("scene1", 32, 32);
    Ares2D::Resource::AddShader("scene1", 1);

    Ares2D::Resource::BindResource("scene1", 1);

    glm::mat4 m_projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    Ares2D::Resource::SetUniformMat4f("scene1", 1, "u_MVP", m_projection);

    TextureUse texture1 = Ares2D::Resource::AddTexture("scene1", "engine/resources/images/nature_tileset/tile000.png");
    TextureUse texture2 = Ares2D::Resource::AddTexture("scene1", "engine/resources/images/nature_tileset/tile040.png");
    TextureUse texture3 = Ares2D::Resource::AddTexture("scene1", "engine/resources/images/nature_tileset/tile002.png");
    TextureUse texture4 = Ares2D::Resource::AddTexture("scene1", "engine/resources/images/nature_tileset/tile003.png");


    /*-------------------------------------------------------------*/
    // Shapes

    Rect rect1(Position{ 700, 200, 300  , 300 }, ARES_NO_COLOR, texture1);
    Rect rect2(Position{ 0  , 0  , 3200, 320 },  ARES_NO_COLOR, texture2);
    Rect rect3(Position{ 500, 700, 32  , 32 },   ARES_NO_COLOR, texture3);
    Rect rect4(Position{ 50 , 450, 100  , 100 }, ARES_NO_COLOR, texture4);

    /*-------------------------------------------------------------*/
    // Audio 

    Ares2D::Audio::add("sandbox/examples/example_shooter/audio/soundtracks/rolling_dontus.wav", 1);
    Ares2D::Audio::play(1, true);


    /*-------------------------------------------------------------*/
    // UI 

    Ares2D::UI::Font boh("engine/utils/ui/fonts/boh.ttf", 75);


    /*-------------------------------------------------------------*/
    // Post-Processing
    //Ares2D::VFX::AddVFX("wavy");


    /*-------------------------------------------------------------*/
    // Clock

    double lastFrameTime = 0.0f;
    
    double previousTime = glfwGetTime();
    int frameCount = 0;
    int fps = 0;

    Ares2D::Window::SetBlending(true);

    /*-------------------------------------------------------------*/
    // Miscellaneous

    bool toggleMemInfo = true;

    /*-------------------------------------------------------------*/
    // Main loop

    while (Ares2D::Window::WindowOpen())
    {
        // Clearing vertices and indices(actually this time)
        Ares2D::Window::Clear(Color{ 16.0f, 16.0f, 16.0f, 1.0f });

        Ares2D::Renderer::Clear();


        if (Ares2D::Input::getIsKeyDown(GLFW_KEY_SPACE))
        {
            toggleMemInfo = !toggleMemInfo;
        }

        Ares2D::Resource::BindResource("scene1", 1);
        Ares2D::Renderer::AddRenderable(rect1);
        Ares2D::Renderer::AddRenderable(rect2);
        Ares2D::Renderer::AddRenderable(rect3);
        Ares2D::Renderer::AddRenderable(rect4);

        Ares2D::Renderer::Draw(false);

        Ares2D::Renderer::Clear();

        Ares2D::UI::RenderText(boh, "Sky", 500, 600, Color{ 0.9f, 0.6f, 0.0f, 1.0f });
        Ares2D::UI::RenderText(boh, "Water", 500, 100, Color{ 0.9f, 0.6f, 0.0f, 1.0f });

        if (toggleMemInfo)
        {
            std::cout << DisplayMemoryInfo() << std::endl;
        }

        // Swap buffers and OS/User events
        Ares2D::Window::Update();
    }
    
    // Terminate after loop over
    Ares2D::Window::Terminate();

    return 0;
}
