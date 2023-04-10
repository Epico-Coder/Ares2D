#include <iostream>

#include "engine/Ares2D.h"

#include "dependancies/glm/glm.hpp"
#include "dependancies/glm/gtc/matrix_transform.hpp"

void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

int main()
{
    Ares2D::GLFWInit();

    Window win(1280, 720, "Abstracted window", true);
    win.MakeContextCurrent();

    Ares2D::GLEWInit();

    // Print OpenGL Version
    std::cout << Ares2D::GetVersion() << std::endl;

    // temp debug here
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    Renderer renderer;

    // Adding Entities into renderer
    Triangle tri1(Vertex{ 040.0f, 260.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f },
                  Vertex{ 240.0f, 260.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
                  Vertex{ 140.0f, 460.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });

    Triangle tri2(Vertex{ 340.0f, 260.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f },
                  Vertex{ 540.0f, 260.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
                  Vertex{ 440.0f, 460.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f });

    renderer.AddGeometry<Triangle>(tri1);
    renderer.AddGeometry<Triangle>(tri2);

    Shader shader;
    shader.AddVertexShader();
    shader.AddFragmentShader();
    shader.Create();
    shader.Bind();

    Input input(win.getWindow());

    std::vector<Geometry> iterable_objs = { tri1, tri2 };
    unsigned int active_obj = 0;

    float i = 0;
    float a = 0.1f;
    // Main Loop
    while (win.WindowOpen())
    {
        win.Clear();

        // Inputs
        
        //std::cout << "ENABLED: " << input.getIsEnabled() << std::endl;
        //std::cout << "KEYBOARD: " << input.getIsKeyDown(GLFW_KEY_0) << std::endl;
        //std::cout << "MOUSE: " << input.getIsKeyDown(GLFW_MOUSE_BUTTON_1) << std::endl;
        //std::cout << "TEXT: " << input.getText() << std::endl;
        //std::cout << "MOUSE_POS: " << input.getMousePos()[0] << ", " << input.getMousePos()[1] << std::endl;
        //std::cout << "CURSOR_ENTERED: " << input.getCursorEntered() << std::endl;
        //std::cout << "SCROLL: " << input.getScrollOffset()[0] << ", " << input.getScrollOffset()[1] << std::endl;

        // Toggle through the Shapes
        if (input.getIsKeyDown(GLFW_KEY_1))
            active_obj = 0;
        if (input.getIsKeyDown(GLFW_KEY_2))
            active_obj = 1;
        if (input.getIsKeyDown(GLFW_KEY_3))
            active_obj = 2;
        if (input.getIsKeyDown(GLFW_KEY_4))
            active_obj = 3;

        // Move Selected Shape
        if (input.getIsKeyDown(GLFW_KEY_LEFT))
            (iterable_objs[active_obj]).Translate(-5.0f, 0.0f);
        if (input.getIsKeyDown(GLFW_KEY_RIGHT))
            iterable_objs[active_obj].Translate(5.0f, 0.0f);
        if (input.getIsKeyDown(GLFW_KEY_UP))
            iterable_objs[active_obj].Translate(0.0f, 5.0f);
        if (input.getIsKeyDown(GLFW_KEY_DOWN))
            iterable_objs[active_obj].Translate(0.0f, -5.0f);

        // Add a Shape
        if (input.getisMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        {
            Rect temp_rect = Rect(Vertex{ float(input.getMousePos()[0]), float(win.getHeight()) - float(input.getMousePos()[1]), i, i, i, 1.0f, 0.0f, 1.0f, 0.0f }, 100.0f, 100.0f);
            renderer.AddGeometry<Rect>(temp_rect);
        }

        // Update Logic
        renderer.Update();

        // Convert range of position vector from -1 to 1, to normal
        // -> Create math class
        glm::mat4 view = glm::ortho(0.0f, float(win.getWidth()), 0.0f, float(win.getHeight()), -1.0f, 1.0f);
        
        glm::mat4 mvp = view;
        shader.SetUniformMat4f("u_MVP", mvp);
        
        // Update ReDraw
        shader.Bind();

        renderer.Draw();

        // Swap back and front buffers
        win.SwapBuffers();
        // OS and User events
        win.PollEvents();

        i += a;
        if ((0.0f > i) or (i > 1.0f)) { a *= -1; }
    }

    // Terminate after loop over
    win.Terminate();

    return 0;
}