#include <iostream>

#include "engine/Ares2D.h"

#include "sandbox/examples/example_shooter/Level/Level.h"
#include "sandbox/examples/example_shooter/Player/Player.h"
#include "sandbox/examples/example_shooter/Enemy/Enemy.h"

#include <algorithm>

using namespace Ares2D;

const float GRAVITY = 9.8f * 50;
const float JETPACK_THRUST = 1000.0f;

const float PLAYER_SPEED = 100.0f;

const float PLAYER_MAX_SPEED = 500.0f;

const std::string PATH = "sandbox/examples/example_shooter/";

// Player variables
glm::vec2 playerPosition(WIDTH / 2, HEIGHT / 2);
glm::vec2 playerVelocity(0.0f, 0.0f);
glm::vec2 playerSize(32.0f, 32.0f);

bool isJetPack = false;

// Update function inside the main loop
void Update(float deltaTime, Rect& plr)
{
    // Apply gravity to the player
    playerVelocity.y -= GRAVITY * deltaTime;

    // Check for user input
    if (USERINPUT.getIsKeyDown(GLFW_KEY_SPACE))
    {
        // Activate the jetpack
        isJetPack = true;
        playerVelocity.y += JETPACK_THRUST * deltaTime;
    }
    else
    {
        isJetPack = false;
    }

    // Control x direction
    if (USERINPUT.getIsKeyDown(GLFW_KEY_LEFT))
    {
        playerVelocity.x -= PLAYER_SPEED * deltaTime;
    }
    else if (USERINPUT.getIsKeyDown(GLFW_KEY_RIGHT))
    {
        playerVelocity.x += PLAYER_SPEED * deltaTime;
    }

    // Clamp player velocity within maximum speed
    playerVelocity.x = glm::clamp(playerVelocity.x, -PLAYER_MAX_SPEED, PLAYER_MAX_SPEED);
    playerVelocity.y = glm::clamp(playerVelocity.y, -PLAYER_MAX_SPEED, PLAYER_MAX_SPEED);

    // Update player position based on velocity
    playerPosition += playerVelocity * deltaTime;

    // Clamp player position within screen boundaries
    if ((playerPosition.x <= 0.0f && playerVelocity.x < 0.0f) || (playerPosition.x >= WIDTH - playerSize.x && playerVelocity.x > 0.0f))
    {
        playerVelocity.x *= -0.25;
    }
    if ((playerPosition.y <= 0.0f && playerVelocity.y < 0.0f) || (playerPosition.y >= HEIGHT - playerSize.y && playerVelocity.y > 0.0f))
    {
        playerVelocity.y *= -0.25;
    }

    playerPosition.x = glm::clamp(playerPosition.x, 0.0f, float(WIDTH - playerSize.x));
    playerPosition.y = glm::clamp(playerPosition.y, 0.0f, float(HEIGHT - playerSize.y));

    std::cout << playerPosition.x << ", " << playerPosition.y << std::endl;

    // Draw the player
    RESOURCE.BindResource("default", 1);
    plr.Add(RENDER, playerPosition.x, playerPosition.y);
    RENDER.Draw();
}

int main()
{

    /*-------------------------------------------------------------*/
    // Init

    Control ctrl = Init(WIDTH, HEIGHT, "Abstracted window");
    std::cout << ctrl.GetVersion() << std::endl;

    ctrl.EnableDebug();

    WIN.SetBlending(true);

    WIN.SetCursorImage(PATH + "images/crosshairs/Outline/CrosshairsOutline01.png");


    /*-------------------------------------------------------------*/
    // Effects

    ARES_VFX.AddVFX("1");

    /*-------------------------------------------------------------*/
    // Fonts

    Font boh(RESOURCE, "engine/utils/ui/fonts/boh.ttf", 12);

    /*-------------------------------------------------------------*/
    // Level setup

    Level level1(&RENDER, &RESOURCE, &USERINPUT, 1, PATH + "data/level1.txt", PATH + "images/backgrounds/1.png", PATH + "images/sprites/player.png");
    
    level1.AddMaterial(1, PATH + "images/terrain/wall_side.png");
    level1.AddMaterial(2, PATH + "images/terrain/wall_up.png");
    level1.AddMaterial(3, PATH + "images/terrain/wall_corner.png");
    level1.AddMaterial(4, PATH + "images/sprites/player.png");

    double lastFrameTime = 0.0f;
    
    double previousTime = glfwGetTime();
    int frameCount = 0;
    int fps = 0;

    // Main Loop
    while (WIN.WindowOpen())
    {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        
        frameCount++;
        // If a second has passed.
        if (currentTime - previousTime >= 1.0)
        {
            fps = frameCount;
            // Display the frame count here any way you want.
            std::cout << frameCount << std::endl;

            frameCount = 0;
            previousTime = currentTime;
        }

        // Binds first Framebuffer
        ARES_VFX.Start();
        
        // Clearing vertices and indices(actually this time)
        WIN.Clear(Color{ 0.0f, 153.0f, 219.0f, 1.0f });
        RENDER.Clear();

        level1.Update(deltaTime);
        level1.Draw();

        // Render text
        USER.RenderText(boh, "FPS: " + std::to_string(fps), 100, 600, Color{0.98f, 0.52f, 0.26f, 0.8f}, 2);

        // Unbinds Framebuffer and draws screen wide rect
        ARES_VFX.End(RENDER);
        
        // Swap buffers and OS/User events
        WIN.Update();
    }
    
    // Terminate after loop over
    WIN.Terminate();

    

    return 0;
}
