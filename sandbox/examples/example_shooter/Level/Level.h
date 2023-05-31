#pragma once

#include "engine/Ares2D.h"

#include "sandbox/examples/example_shooter/Player/Player.h"
#include "sandbox/examples/example_shooter/Enemy/Enemy.h"

#include "engine/utils/input/Input.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <optional>

const int WIDTH = 1280;
const int HEIGHT = 720;

const int ROWS = 32;
const int COLS = 18;

const int SIZEX = WIDTH / ROWS;
const int SIZEY = HEIGHT / COLS;

class Level {
    friend class Player;
public:
    Level(int levelNumber, const std::string& level_path, const std::string& bg_path, const std::string& player_path);

    void AddMaterial(int matNumber, const std::string& mat_path);
    void AddEnemy(Enemy& enemy);

    void Update(float deltaTime, glm::vec2 mouse_pos);
    void Draw();
private:
    std::optional<Position> Collision(int x, int y, int w, int h);

    void DrawMap();

    std::vector<std::vector<int>> ReadTextFile(const std::string& filePath)
    {
        std::vector<std::vector<int>> level_matrix;

        std::ifstream inputFile(filePath);

        if (inputFile.is_open())
        {
            std::string line;
            while (std::getline(inputFile, line)) {
                std::vector<int> row;
                for (char c : line) {
                    int value = c - '0';
                    row.push_back(value);
                }
                level_matrix.push_back(row);
            }

            inputFile.close();  // Close the file
        }
        else
        {
            std::cerr << "Failed to open the file: " << filePath << std::endl;
        }

        return level_matrix;
    }
    void WriteTextFile(const std::string& filePath, const std::vector<std::vector<int>>& level_matrix) {

        std::ofstream outputFile(filePath);

        if (outputFile.is_open())
        {
            for (int i = 0; i < COLS; ++i)
            {
                for (int j = 0; j < ROWS; ++j)
                {
                    outputFile << level_matrix[i][j];
                }
                outputFile << std::endl;
            }
            outputFile.close();
            std::cout << "File written successfully." << std::endl;
        }

        else
        {
            std::cout << "Unable to create file." << std::endl;
        }
    }
private:
    int m_level_no;
    std::vector<std::vector<int>> m_level_matrix;
    std::unordered_map<int, Rect> m_level_map;
    const std::string m_level_path;

    Player* m_player;

    std::vector<Enemy> m_enemies;

    Rect m_bg;
    int m_bgX = 0;
    int m_bgA = 1;

    glm::vec2 m_offsets{ 0, 0 };
    float m_offsetA = 0.1f;
};
