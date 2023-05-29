#pragma once

#include "engine/Ares2D.h"

#include <functional>
#include <optional>

class Bullet {
public:
    Bullet(ResourceHandler& resource, int levelNumber, glm::vec2 startPos, float angle)
        : position(startPos)
    {
        TextureUse t_bullet = resource.AddTexture(std::to_string(levelNumber), "sandbox/examples/example_shooter/images/bullet.png");
        m_rect = new Rect(Position{ startPos.x, startPos.y, size.x, size.y }, ARES_NO_COLOR, t_bullet);
        m_rect->SetAngle(angle);
        velocity *= glm::vec2(cos(angle), sin(-angle));
    }

    void Update(float deltaTime)
    {
        position += velocity * deltaTime;
        m_rect->SetPos(position.x, position.y);
    }

    void Draw(Renderer& renderer)
    {
        m_rect->Add(renderer);
    }
public:
    glm::vec2 size {16, 16};
    glm::vec2 position;
    glm::vec2 velocity{1000, 1000};
    Rect* m_rect;
};

class Player {
    friend class Level;
public:
    Player(ResourceHandler& resource, int levelNumber, const std::string& player_path, std::function<std::optional<Position>(int, int, int, int)> collision_func);

    void Move(float dx, float dy);

    void Update(float deltaTime, glm::vec2 mouse_pos);

    void Draw(Renderer& renderer);

    void ActiveJetpack();
    void DeactivateJetpack();

    void DashLeft();
    void DashRight();

    void Shoot(ResourceHandler& resource);
private:
    Rect* m_rect;

    std::function<std::optional<Position>(int, int, int, int)> m_collision_func;

    int m_level_number;

    // -1: left, 0: none, 1: right
    int isDashing = 0;
    glm::vec2 dashStartPosition;

    float dashTimer = 0.0f;
    float dashDuration = 0.25f;

    float dashForce = 750.0f;
    float dashCooldown = 1.5f;
    float lastDashTime = 0.0f;

    bool isJetpack = false;
    float jetpackForce = 500.0f;
    float damping = 0.9f;

    float gravity = -100.0f;
    float terminal_velocity = 200.0f;

    glm::vec2 size{ 32.0f, 32.0f };

    glm::vec2 position{ 500.0f, 600.0f };
    glm::vec2 velocity{ 0.0f, 0.0f };
    glm::vec2 acceleration{ 0.0f, gravity};

    float m_angle = 0.0f;
    std::vector<Bullet*> m_bullets;
};
