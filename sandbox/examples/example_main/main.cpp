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

    // Adding Entities into renderer

    Triangle tri1(Vertex{ 040.0f, 260.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f },
                  Vertex{ 240.0f, 260.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
                  Vertex{ 140.0f, 460.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });

    Triangle tri2(Vertex{ 340.0f, 260.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f },
                  Vertex{ 540.0f, 260.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
                  Vertex{ 440.0f, 460.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });

    Rect rect1(Vertex{ 640.0f, 260.0f, 1.0f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f }, 100.0f, 250.0f);

    Rect rect2(Vertex{ 640.0f, 260.0f, 1.0f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f },
               Vertex{ 940.0f, 260.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f },
               Vertex{ 940.0f, 360.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
               Vertex{ 640.0f, 360.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });

    renderer.AddGeometry<Triangle>(&tri1);
    renderer.AddGeometry<Rect>(&rect1);
    renderer.AddGeometry<Triangle>(&tri2);
    renderer.AddGeometry<Rect>(&rect2);

    Shader shader;
    shader.AddVertexShader();
    shader.AddFragmentShader();
    shader.Create();
    shader.Bind();

    KeyInput ki(win.getWindow());

    std::vector<Geometry*> iterable_objs = { &tri1, &tri2, &rect1, &rect2 };
    unsigned int active_obj = 0;

    // Main Loop
    while (win.WindowOpen())
    {
        win.Clear(25, 25, 25);

        // Inputs
        
        // Toggle through the triangles
        // -> Custom key definitions
        if (ki.getIsKeyDown(GLFW_KEY_TAB))
        {
            if (active_obj >= iterable_objs.size() - 1)
                active_obj = 0;
            else
                active_obj++;
        }

        if (ki.getIsKeyDown(GLFW_KEY_1))
            active_obj = 0;
        if (ki.getIsKeyDown(GLFW_KEY_2))
            active_obj = 1;
        if (ki.getIsKeyDown(GLFW_KEY_3))
            active_obj = 2;
        if (ki.getIsKeyDown(GLFW_KEY_4))
            active_obj = 3;

        // -> Key mapping to functions
        if (ki.getIsKeyDown(GLFW_KEY_LEFT))
            (iterable_objs[active_obj])->Translate(-5.0f, 0.0f);
        if (ki.getIsKeyDown(GLFW_KEY_RIGHT))
            iterable_objs[active_obj]->Translate(5.0f, 0.0f);
        if (ki.getIsKeyDown(GLFW_KEY_UP))
            iterable_objs[active_obj]->Translate(0.0f, 5.0f);
        if (ki.getIsKeyDown(GLFW_KEY_DOWN))
            iterable_objs[active_obj]->Translate(0.0f, -5.0f);

        // Update Logic
        renderer.Update();

        // Convert range of position vector from -1 to 1, to normal
        // -> Create math class
        glm::mat4 mvp = glm::ortho(0.0f, float(win.getWidth()), 0.0f, float(win.getHeight()), -1.0f, 1.0f);
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