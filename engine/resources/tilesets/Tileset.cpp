#include "Tileset.h"

#include <iostream>

Tileset::Tileset(TextureHandler& texture_handler, const std::string& filePath, int rows, int cols, float size_mult)
{
	std::vector<int> size = texture_handler.GetSize(filePath);
	m_sheetWidth = size[0];
	m_sheetHeight = size[1];

	texture_handler.AddTextureArray("Tileset", m_sheetWidth, m_sheetHeight);
	texture_handler.AddTexture("Tileset", filePath);
	texture_handler.Bind();

	m_rows = rows;
	m_cols = cols;

	m_tileWidth = m_sheetWidth / m_rows;
	m_tileHeight = m_sheetHeight / m_cols;
	std::cout << m_sheetHeight << std::endl;

	m_Tiles.resize(cols, std::vector<Rect>(rows));
	std::cout << m_Tiles.size() << std::endl;

	for (int j = 0; j < cols; j++)
	{
		for (int i = 0; i < rows; i++)
		{
			Rect tile(0.0f, 0.0f, m_tileWidth * size_mult, m_tileHeight * size_mult, float(texture_handler.GetNumTextures()), 0.0f);
			tile.SetTexCords(float(((i + 0) * m_tileWidth) / m_sheetWidth), float(((j + 1) * m_tileHeight) / m_sheetHeight),
							 float(((i + 1) * m_tileWidth) / m_sheetWidth), float(((j + 1) * m_tileHeight) / m_sheetHeight),
							 float(((i + 1) * m_tileWidth) / m_sheetWidth), float(((j + 0) * m_tileHeight) / m_sheetHeight),
							 float(((i + 0) * m_tileWidth) / m_sheetWidth), float(((j + 0) * m_tileHeight) / m_sheetHeight));
			m_Tiles[j][i] = tile;
		}
	}
}

Tileset::~Tileset()
{
}

Rect Tileset::GetTile(int row, int col)
{
	return m_Tiles[col][row];
}

void Tileset::DrawTilePositions(Renderer& renderer, int win_width, int win_height, std::vector<std::vector<std::pair<unsigned int, unsigned int>>> tile_positions)
{
	int n_rows = (win_height / tile_positions.size());

	for (int j = 0; j < tile_positions.size(); j++)
	{
		int n_cols = win_width / tile_positions[j].size();

		for (int i = 0; i < tile_positions[j].size(); i++)
		{
			int row = tile_positions[j][i].second;
			int col = tile_positions[j][i].first;

			Rect temp = GetTile(row, col);

			temp.Draw(renderer, ((n_cols / 2) + (i * n_cols)), 
								win_height - ((n_rows / 2) + (j * n_rows)));
		}
	}
}
