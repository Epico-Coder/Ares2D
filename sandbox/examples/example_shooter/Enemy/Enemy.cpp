#include "Enemy.h"

Enemy::Enemy(float x, float y, float width, float height)
    : enemyRect(Position{ x, y, width, height }, Color{ 1.0f, 0.0f, 0.0f, 1.0f }) {}

void Enemy::Move(float dx, float dy) 
{
    enemyRect.SetPos(enemyRect.GetPos().x + dx, enemyRect.GetPos().y + dy);
}

void Enemy::Update(float deltaTime)
{
}

void Enemy::Draw() 
{
    Ares2D::Renderer::AddRenderable(enemyRect);
}
