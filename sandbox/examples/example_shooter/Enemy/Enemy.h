#pragma once

#include "engine/Ares2D.h"

class Enemy {
public:
    Enemy(float x, float y, float width, float height);

    void Move(float dx, float dy);

    void Update(float deltaTime);

    void Draw();
private:
    Rect enemyRect;
};