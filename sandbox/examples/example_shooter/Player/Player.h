#pragma once

#include "engine/Ares2D.h"

class Player {
public:
    Player(ResourceHandler& resource, int levelNumber, const std::string& player_path);

    void Move(float dx, float dy);

    void Update(float deltaTime);

    void Draw(Renderer& renderer);
public:
    int x = 0;
    int y = 0;
private:
    Rect* m_rect;

    bool jetpackActive;
};