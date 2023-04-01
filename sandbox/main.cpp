#include <iostream>

#include "engine/Ares2D.h"

#include "dependancies/glm/glm.hpp"
#include "dependancies/glm/gtc/matrix_transform.hpp"

int main()
{
    Ares2D::GLFWInit();

    Window win(1280, 720, "Abstracted window", true);
    win.MakeContextCurrent();

    Ares2D::GLEWInit();

    // Print OpenGL Version
    std::cout << Ares2D::GetVersion() << std::endl;

    Renderer renderer;

    // List of Positions to be stored in vertex buffer
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };

    // List of Indices to be stored in index buffer
    unsigned int indices[] = {
        0, 1, 2,    
    };

    // Adding Entities into renderer
    TrianglePS trips{ -0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f };
    Color clr{ 1.0f, 0.8f, 0.2f, 1.0f };
    Triangle tri(trips, clr, 1.0f);

    renderer.AddTriangle("triangle 1", tri);
    
    // iterator, acceleration
    float i = 0.0f;
    float a = 0.01f;

    // Main Loop
    while (win.WindowOpen())
    {
        win.Clear(255, 155, 0);
        
        // Update Logic

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0, 0));
        glm::vec4 new_vert1 = view * glm::vec4(-0.5f, -0.5f, 1.0f, 1.0f);
        glm::vec4 new_vert2 = view * glm::vec4(0.5f, -0.5f, 1.0f, 1.0f);
        glm::vec4 new_vert3 = view * glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);
        TrianglePS trips{ new_vert1.x, new_vert1.y, new_vert2.x, new_vert2.y, new_vert3.x, new_vert3.y };
        Triangle tri(trips, clr, 1.0f);

        renderer.UpdateTriangle("triangle 1", tri);

        // Update ReDraw

        renderer.Draw();

        // Swap back and front buffers
        win.SwapBuffers();
        // OS and User events
        win.PollEvents();

        if (i >= 0.5f || i <= -0.5f)
            a *= -1;
        i += a;
    }

    // Terminate after loop over
    win.Terminate();

    return 0;
}