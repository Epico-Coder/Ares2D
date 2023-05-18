#include "Player.h"


Player::Player(ResourceHandler& resource, int levelNumber, const std::string& player_path)
{
    TextureUse t_plr = resource.AddTexture(std::to_string(levelNumber), player_path);
    m_rect = new Rect(Position{ float(x), float(y), 32, 32 }, ARES_NO_COLOR, t_plr);
}

void Player::Move(float dx, float dy)
{
    x += dx;
    y += dy;
}

void Player::Update(float deltaTime)
{

}

void Player::Draw(Renderer& renderer) 
{
    m_rect->Add(renderer, x, y);
}
