#include "Level.h"

Level::Level(Renderer* renderer, ResourceHandler* resource, InputHandler* input, int levelNumber, const std::string& level_path, const std::string& bg_path, const std::string& player_path)
    : m_renderer(renderer), m_resource(resource), m_input(input), m_level_no(levelNumber), m_level_path(level_path)
{
    m_resource->AddResource(std::to_string(m_level_no), 1200, 600);
    m_resource->AddShader(std::to_string(m_level_no), 1);

    TextureUse t_bg = m_resource->AddTexture(std::to_string(m_level_no), bg_path);
    m_bg = Rect(Position{ 0, 0, WIDTH, HEIGHT }, ARES_NO_COLOR, t_bg);

    m_player = new Player(*m_resource, levelNumber, player_path, [this](int x, int y, int w, int h) {return Collision(x, y, w, h);});

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

void Level::Update(float deltaTime, glm::vec2 mouse_pos)
{
    m_resource->BindResource(std::to_string(m_level_no), 1);

    // Move background
    if (m_bgX < -WIDTH)
        m_bgX = m_bgX % WIDTH;

    m_bgX -= m_bgA;

    // Move level
    if ((m_offsets.x + m_offsetA + ROWS) < m_level_matrix[0].size())
    {
        m_offsets.x += m_offsetA;
        m_offsets.y += 0;
    }

    // Inputs

    

    // Up or Space: Activate Jetpack
    if ((m_input->getIsKeyDown(GLFW_KEY_UP) || m_input->getIsKeyDown(GLFW_KEY_SPACE)))
        m_player->ActiveJetpack();
    else
        m_player->DeactivateJetpack();

    // Left and Right: Dashes
    if (m_input->getIsKeyDown(GLFW_KEY_LEFT))
        m_player->DashLeft();
    else if (m_input->getIsKeyDown(GLFW_KEY_RIGHT))
        m_player->DashRight();

    // Cursor hover: Aim
    // Cursor click: Shoot

    if (m_input->getisMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
        m_player->Shoot(*m_resource);

    // Respond to collisions

    // Update player
    m_player->Update(deltaTime, mouse_pos);

    // Update Enemies
    for (auto& enemy : m_enemies)
    {
        enemy.Update(deltaTime);
    }
}

std::optional<Position> Level::Collision(int x, int y, int w, int h)
{
    for (int i = m_offsets.y; i < (COLS + m_offsets.y); i++)
    {
        const auto& row = m_level_matrix[i];

        for (int j = m_offsets.x; j < (ROWS + m_offsets.x); j++)
        {
            if (m_level_matrix[i][j] != 0)
            {
                int tile_x = SIZEX * (j - m_offsets.x);
                int tile_y = HEIGHT - (SIZEY * (i + 1 - m_offsets.y));
                int tile_w = SIZEX;
                int tile_h = SIZEY;
                if ((tile_x < x) && (x < tile_x + tile_w) &&
                    (tile_y < y) && (y < tile_y + tile_h))
                {
                    std::cout << "COLLIDED" << std::endl;
                    return Position(tile_x, tile_y, tile_w, tile_h);
                }
            }
        }
    }

    return std::nullopt;
}

void Level::DrawMap()
{
    for (int i = m_offsets.y; i < (COLS + m_offsets.y); i++)
    {
        const auto& row = m_level_matrix[i];

        for (int j = m_offsets.x; j < (ROWS + m_offsets.x); j++)
        {
            m_level_map[m_level_matrix[i][j]].Add(*m_renderer, SIZEX * (j - m_offsets.x), HEIGHT - (SIZEY * (i+1 - m_offsets.y)));
        }
    }
}

void Level::Draw()
{
    m_resource->BindResource(std::to_string(m_level_no), 1);

    // Moving Bg
    m_bg.Add(*m_renderer, m_bgX, 0);
    m_bg.Add(*m_renderer, m_bgX + WIDTH, 0);

    m_renderer->Draw(false);

    DrawMap();

    m_player->Draw(*m_renderer);

    for (auto& enemy : m_enemies)
        enemy.Draw();

    m_renderer->Draw(false);
}