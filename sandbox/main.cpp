#include "../dependancies/glew/include/GL/glew.h"
#include "../dependancies/glfw/include/GLFW/glfw3.h"

#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();

int main()
{
    // Create window
    GLFWwindow* window;

    // Handling Initialization Error of GLFW
    if (!glfwInit())
    {
        std::cout << "GLEW Not Initialized!" << std::endl;
        return -1;
    }

    // Set Width and Height of Window
    int WIDTH = 1280, HEIGHT = 720;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "Quad Transformations", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);
    
    // Handling Initialization Error of GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW Not Initialized!" << std::endl;
        return -1;
    }

    // Print OpenGL Version
    std::cout << glGetString(GL_VERSION) << std::endl;

    /* -------------------------------------------------------------------- */
    
    glEnable(GL_DEPTH_TEST);

    double translate_x = 0;
    double translate_y = 0;
    double scale = 1;;
    double rotate = 0;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);

        // Reset transformations
        glLoadIdentity();

        // Other Transformations
        glTranslatef( translate_x, translate_y, 0.0 );

        // Rotate when user changes rotate_x and rotate_y
        glRotatef(rotate, 0.0, 0.0, 1.0);
        
        // Other Transformations
        glScalef( scale, scale, 0.0 );

        // Legacy OpenGL - Testing
        glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);     
        glVertex3f(0.5, -0.5, -0.5);
        glColor3f(0.0, 1.0, 0.0);     
        glVertex3f(0.5, 0.5, -0.5);
        glColor3f(0.0, 0.0, 1.0);     
        glVertex3f(-0.5, 0.5, -0.5);
        glColor3f(1.0, 0.0, 1.0);     
        glVertex3f(-0.5, -0.5, -0.5);
        glEnd();

        // Input
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
            translate_x -= 0.1;
        
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
            translate_x += 0.1;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
            translate_y += 0.1;

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) 
            translate_y -= 0.1;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
            scale += 0.1;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
            scale -= 0.1;

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            rotate += 1;
        

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

    }

    // Terminate after loop over
    glfwTerminate();

    return 0;
}