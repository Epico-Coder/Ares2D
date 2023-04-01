#include <iostream>

#include "engine/Ares2D.h"

int main()
{
    Ares2D::GLFWInit();

    Window win(1280, 720, "Abstracted window", true);
    win.MakeContextCurrent();

    Ares2D::GLEWInit();

    // Print OpenGL Version
    std::cout << Ares2D::GetVersion() << std::endl;

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

    // -> Rect rect(Entps, Color, Texture);
    // -> rect.Draw();

    VertexBuffer vb(vertices, 3 * 2 * sizeof(float));

    VertexBufferLayout vbl;
    vbl.Push<GLfloat>(2);

    VertexArray vao;
    vao.AddBuffer(vb, vbl);

    IndexBuffer ib(indices, 3);

    // Main Loop
    while (win.WindowOpen())
    {
        win.Clear(255, 155, 0);
        
        // Update Logic


        // Update ReDraw

        vao.Bind();
        glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

        // Swap back and front buffers
        win.SwapBuffers();
        // OS and User events
        win.PollEvents();
    }

    // Terminate after loop over
    win.Terminate();

    return 0;
}