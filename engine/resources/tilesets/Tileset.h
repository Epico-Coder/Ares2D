#pragma once

#include "engine/rendering/geometry/Rect.h"
#include "engine/resources/textures/Texture.h"
#include <string>
#include <vector>

class Tileset
{
public:
	Tileset(Shader& shader, TextureHandler& texture_handler, const std::string& filePath, int rows, int cols, float size_mult = 1);
	~Tileset();

	Rect GetTile(int row, int col);
	void DrawTilePositions(Renderer& renderer, int win_width, int win_height, std::vector<std::vector<std::pair<unsigned int, unsigned int>>> tile_positions);
	std::vector<std::vector<Rect>>m_Tiles;
private:
	float m_sheetWidth;
	float m_sheetHeight;

	float m_tileWidth;
	float m_tileHeight;

	int m_rows;
	int m_cols;
};

