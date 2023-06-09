#include "Level.h"

Level::Level(int levelNumber, const std::string& level_path, const std::string& bg_path, const std::string& player_path)
    : m_level_no(levelNumber), m_level_path(level_path)
{
   Ares2D::Resource::AddResource(std::to_string(m_level_no), 1200, 600);
   Ares2D::Resource::AddShader(std::to_string(m_level_no), 1);

    TextureUse t_bg = Ares2D::Resource::AddTexture(std::to_string(m_level_no), bg_path);
    m_bg = Rect(Position{ 0, 0, WIDTH, HEIGHT }, ARES_NO_COLOR, t_bg);

    m_player = new Player(levelNumber, player_path, [this](int x, int y, int w, int h) {return Collision(x, y, w, h);});

    Ares2D::Resource::BindResource(std::to_string(m_level_no), 1);

    // Sets uniforms only once since 2D view doesnt change
    glm::mat4 projectionMatrix = glm::ortho(0.0f, float(WIDTH), 0.0f, float(HEIGHT), -1.0f, 1.0f);
    Ares2D::Resource::SetUniformMat4f(std::to_string(m_level_no), 1, "u_MVP", projectionMatrix);

    m_level_matrix = ReadTextFile(m_level_path);
}

void Level::AddMaterial(int matNumber, const std::string& mat_path)
{
    TextureUse t_material = Ares2D::Resource::AddTexture(std::to_string(m_level_no), mat_path);
    Rect r_material(Position{ 0, 0, SIZEX, SIZEY }, ARES_NO_COLOR, t_material);

    m_level_map[matNumber] = r_material;
}

void Level::AddEnemy(Enemy& enemy)
{
    m_enemies.push_back(enemy);
}

void Level::Update(float deltaTime, glm::vec2 mouse_pos)
{
    Ares2D::Resource::BindResource(std::to_string(m_level_no), 1);

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
    if ((Ares2D::Input::getIsKeyDown(GLFW_KEY_UP) || Ares2D::Input::getIsKeyDown(GLFW_KEY_SPACE)))
    {
        m_player->ActiveJetpack();
    }
    else
    {
        m_player->DeactivateJetpack();
    }

    // Left and Right: Dashes
    if (Ares2D::Input::getIsKeyDown(GLFW_KEY_LEFT))
    {
        m_player->DashLeft();
    }
    else if (Ares2D::Input::getIsKeyDown(GLFW_KEY_RIGHT))
    {
        m_player->DashRight();
    }

    // Cursor hover: Aim
    // Cursor click: Shoot

    if (Ares2D::Input::getIsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
    {
        m_player->Shoot();
    }

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
            m_level_map[m_level_matrix[i][j]].SetPos(SIZEX * (j - m_offsets.x), HEIGHT - (SIZEY * (i+1 - m_offsets.y)));
            Ares2D::Renderer::AddRenderable(m_level_map[m_level_matrix[i][j]]);
        }
    }
}

void Level::Draw()
{
    Ares2D::Resource::BindResource(std::to_string(m_level_no), 1);

    // Moving Bg
    m_bg.SetPos(m_bgX, 0);
    Ares2D::Renderer::AddRenderable(m_bg);
    m_bg.SetPos(m_bgX + WIDTH, 0);
    Ares2D::Renderer::AddRenderable(m_bg);

    Ares2D::Renderer::Draw();

    DrawMap();

    m_player->Draw();

    for (auto& enemy : m_enemies)
        enemy.Draw();

    Ares2D::Renderer::Draw();
}