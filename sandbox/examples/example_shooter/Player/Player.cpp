#include "Player.h"

Player::Player(int levelNumber, const std::string& player_path, std::function<std::optional<Position>(int, int, int, int)> collision_func)
    : m_level_number(levelNumber), m_collision_func(collision_func)
{
    TextureUse t_plr = Ares2D::Resource::AddTexture(std::to_string(m_level_number), player_path);
    m_rect = new Rect(Position{ position.x, position.y, size.x, size.y }, ARES_NO_COLOR, t_plr);
}

void Player::Move(float dx, float dy)
{
    position.x += dx;
    position.y += dy;
}

void Player::Update(float deltaTime, glm::vec2 mouse_pos)
{
    // Clamp the velocities to a maximum
    velocity.y = max(velocity.y, -terminal_velocity);
    velocity.y = min(velocity.y, terminal_velocity);

    // Jetpack
    if (isJetpack)
    {
        velocity.y += jetpackForce * deltaTime;
    }
    else
    {
        if (velocity.y > 0)
        {
            velocity.y *= damping;
        }
    }

    // Dashing
    lastDashTime += deltaTime;

    if (isDashing != 0)
    {
        if (dashTimer < dashDuration)
        {
            // Calculate new position
            glm::vec2 targetPosition = dashStartPosition + glm::vec2(isDashing * dashForce * deltaTime, 0);
            glm::vec2 newPosition = glm::mix(dashStartPosition, targetPosition, dashTimer / dashDuration);

            // Move to new position
            position = newPosition;

            // Update dash timer
            dashTimer += deltaTime;
        }
        else
        {
            dashTimer = 0.0f;

            isDashing = 0;
            lastDashTime = 0.0f;
        }
    }

    // Bullets
    for (auto it = m_bullets.begin(); it != m_bullets.end();)
    {
        if (((*it)->position.x < 0) || ((*it)->position.x + (*it)->size.x > 1280))
        {
            delete* it;
            it = m_bullets.erase(it);
        }
        if (((*it)->position.y < 0) || ((*it)->position.y + (*it)->size.y > 720))
        {
            delete* it;
            it = m_bullets.erase(it);
        }
        else
        {
            (*it)->Update(deltaTime);
            ++it;
        }
    }

    // Calculate direction from player to cursor
    glm::vec2 dir = glm::normalize(mouse_pos - position);
    dir.y *= -1;

    // Calculate the angle for the arrow
    m_angle = atan2(dir.y, dir.x);

    m_rect->SetAngle(m_angle);

    velocity += acceleration * deltaTime;
    glm::vec2 new_position = position + velocity * deltaTime;

    position.x += velocity.x * deltaTime;

    auto pos = m_collision_func(position.x, position.y, size.x, size.y);
    if (pos.has_value())
    {
        
        if (velocity.x < 0)
        {
            position.x = pos->x + pos->w;
            velocity.x = 0;
        }
        if (velocity.x > 0)
        {
            position.x = pos->x - size.x;
            velocity.x = 0;
        }
        
        //position.x += -velocity.x * deltaTime;
    }

    position.y += velocity.y * deltaTime;

    pos = m_collision_func(position.x, position.y, size.x, size.y);
    if (pos.has_value())
    {
        
        if (velocity.y < 0)
        {
            position.y = pos->y + pos->h;
            velocity.y = 0;
        }
        if (velocity.y > 0)
        {
            position.y = pos->y - size.y;
            velocity.y = 0;
        }
        
        //position.y += -velocity.y * deltaTime;
    }

    m_rect->SetPos(position.x, position.y);
}

void Player::Draw() 
{
    std::cout << "Postion: " << position.x << ", " << position.y << std::endl;
    Ares2D::Renderer::AddRenderable(*m_rect);

    for (auto bullet : m_bullets)
    {
        bullet->Draw();
    }
}

void Player::ActiveJetpack()
{
    isJetpack = true;
}

void Player::DeactivateJetpack()
{
    isJetpack = false;
}

void Player::DashLeft()
{
    velocity.x -= 5;
    /*
    if (lastDashTime >= dashCooldown)
    {
        isDashing = -1;
        dashStartPosition = position;
    }
    */
}

void Player::DashRight()
{
    velocity.x += 5;
    /*
    if (lastDashTime >= dashCooldown)
    {
        isDashing = 1;
        dashStartPosition = position;
    }
    */
}

void Player::Shoot()
{
    m_bullets.push_back(new Bullet(m_level_number, position, m_angle));
}
