#include "engine/Ares2D.h"

#include <iostream>

int main()
{
    if (!Ares2D::Init())
        std::cout << "Initialization Error" << std::endl;

    Window win(1280, 720, "Abstracted window", true);

    // Print OpenGL Version
    std::cout << Ares2D::GetVersion() << std::endl;

    // Main Loop
    while (win.WindowOpen())
    {
        win.Clear(200.0f, 120.0f, 0.0f, 255.0f);
        
        // Update Logic


        // Update ReDraw
        
        Renderer renderer;
        renderer.DrawTestTriangle(-0.5f, -0.5f, 0.25f);
        renderer.DrawTestTriangle( 0.5f, -0.5f, 0.25f);

        win.SwapBuffers();
        win.PollEvents();

    }

    // Terminate after loop over
    win.Terminate();

    return 0;
}