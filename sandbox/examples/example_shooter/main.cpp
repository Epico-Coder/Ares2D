#include "engine/Ares2D.h"

#include <algorithm>

void example()
{

}

int main()
{
    /*-------------------------------------------------------------*/
    // Init

    const int WIDTH = 1280;
    const int HEIGHT = 720;

    const std::string PATH = "sandbox/examples/example_shooter/";

    Ares2D::Init(WIDTH, HEIGHT, "Abstracted window");

    Ares2D::Window::SetBlending(true);

    Ares2D::Window::SetCursorImage(PATH + "images/crosshairs/Outline/CrosshairsOutline01.png");
    /*-------------------------------------------------------------*/
    // Testing

    Rect hello(Position{ 30, 30, 50, 50 }, Color{ 255, 0, 0, 255 }, 0);
    
    /*-------------------------------------------------------------*/
    // Level setup

    /*
    Level level1(&RESOURCE, &USERINPUT, 1, PATH + "data/level1.txt", PATH + "images/backgrounds/1.png", PATH + "images/sprites/player.png");
    
    level1.AddMaterial(1, PATH + "images/terrain/wall_side.png");
    level1.AddMaterial(2, PATH + "images/terrain/wall_up.png");
    level1.AddMaterial(3, PATH + "images/terrain/wall_corner.png");
    level1.AddMaterial(4, PATH + "images/sprites/player.png");
    */

    double lastFrameTime = 0.0f;
    
    double previousTime = glfwGetTime();
    int frameCount = 0;
    int fps = 0;

    // Main Loop
    while (Ares2D::Window::WindowOpen())
    {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        
        frameCount++;

        // If a second has passed.
        if (currentTime - previousTime >= 1.0)
        {
            fps = frameCount;
            frameCount = 0;
            previousTime = currentTime;
        }
        
        auto mouse_pos = Ares2D::Input::getMousePos();
        std::cout << mouse_pos[0] << std::endl;

        // Clearing vertices and indices(actually this time)
        Ares2D::Window::Clear(Color{ 0.0f, 153.0f, 219.0f, 1.0f });
        
        Ares2D::Renderer::Clear();

        Ares2D::Renderer::AddRenderable(hello);
        Ares2D::Renderer::Draw(true);
        
        // Swap buffers and OS/User events
        Ares2D::Window::Update();
    }
    
    // Terminate after loop over
    Ares2D::Window::Terminate();

    return 0;
}
