#include "Level.h"

Level::Level(Renderer* renderer, ResourceHandler* resource, InputHandler* input, int levelNumber, const std::string& level_path, const std::string& bg_path, const std::string& player_path)
    : m_renderer(renderer), m_resource(resource), m_input(input), m_level_no(levelNumber), m_level_path(level_path)
{
    m_resource->AddResource(std::to_string(m_level_no), 1200, 600);
    m_resource->AddShader(std::to_string(m_level_no), 1);

    TextureUse t_bg = m_resource->AddTexture(std::to_string(m_level_no), bg_path);
    m_bg = Rect(Position{ 0, 0, WIDTH, HEIGHT }, ARES_NO_COLOR, t_bg);

    m_player = new Player(*m_resource, levelNumber, player_path);

    m_resource->BindResource(std::to_string(m_level_no), 1);

    // Sets uniforms only once since 2D view doesnt change
    glm::mat4 projectionMatrix = glm::ortho(0.0f, float(WIDTH), 0.0f, float(HEIGHT), -1.0f, 1.0f);
    m_resource->SetUniformMat4f(std::to_string(m_level_no), 1, "u_MVP", projectionMatrix);

    m_level_matrix = ReadTextFile(m_level_path);
}

void Level::AddMaterial(int matNumber, const std::string& mat_path)
{
    TextureUse t_material = m_resource->AddTexture(std::to_string(m_level_no), mat_path);
    Rect r_material(Position{ 0, 0, SIZEX, SIZEY }, ARES_NO_COLOR, t_material);

    m_level_map[matNumber] = r_material;
}

void Level::AddEnemy(Enemy& enemy)
{
    m_enemies.push_back(enemy);
}

void Level::Update(float deltaTime)
{
    m_resource->BindResource(std::to_string(m_level_no), 1);

    // Move background
    if (m_bgX < -WIDTH)
    {
        m_bgX = m_bgX % WIDTH;
    }

    m_bgX -= m_bgA;

    float playerSpeed = 250 * deltaTime;

    // Take inputs and move player, also move the level map if player is going out of bounds
    if (m_input->getIsKeyDown(GLFW_KEY_LEFT))
    {
        if (m_player->x < (2 * SIZEX) && (m_offsetX > 1))
            m_offsetX--;
        else
            m_player->Move(-playerSpeed, 0);
    }
    if (m_input->getIsKeyDown(GLFW_KEY_RIGHT))
    {
        if (m_player->x > (WIDTH - (2 * SIZEX)) && (float(m_offsetX + ROWS) < m_level_matrix[0].size()))
            m_offsetX++;
        else
            m_player->Move(playerSpeed, 0);
    }
    if (m_input->getIsKeyDown(GLFW_KEY_UP))
    {
        if (m_player->y > (HEIGHT - (2 * SIZEY)) && (m_offsetY > 1))
            m_offsetY--;
        else
            m_player->Move(0, playerSpeed);
    }
    if (m_input->getIsKeyDown(GLFW_KEY_DOWN))
    {
        if (m_player->y < (2 * SIZEY) && (float(m_offsetY + COLS) < m_level_matrix.size()))
            m_offsetY++;
        else
            m_player->Move(0, -playerSpeed);
    }
    
    // Update characters
    m_player->Update(deltaTime);

    for (auto& enemy : m_enemies)
    {
        enemy.Update(deltaTime);
    }
}

void Level::DrawMap()
{
    for (int i = m_offsetY; i < (COLS + m_offsetY); i++) 
    {
        const auto& row = m_level_matrix[i];

        for (int j = m_offsetX; j < (ROWS + m_offsetX); j++) 
        {
            m_level_map[m_level_matrix[i][j]].Add(*m_renderer, SIZEX * (j - m_offsetX), HEIGHT - (SIZEY * (i+1 - m_offsetY)));
        }
    }
}

void Level::Draw()
{
    m_resource->BindResource(std::to_string(m_level_no), 1);

    // Moving Bg
    m_bg.Add(*m_renderer, m_bgX, 0);
    m_bg.Add(*m_renderer, m_bgX + WIDTH, 0);

    DrawMap();

    m_player->Draw(*m_renderer);

    for (auto& enemy : m_enemies)
        enemy.Draw();

    m_renderer->Draw();
}