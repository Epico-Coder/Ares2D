#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "engine/resources/shaders/Shader.h"
#include <string>
#include <vector>

class Texture
{
public:
	Texture(int width, int heigth);
	~Texture();

	void Bind();
	void Unbind();

	unsigned int getID() const;
private:
	unsigned int m_buffer;
};

class TextureHandler
{
public:
	TextureHandler();
	~TextureHandler();

	unsigned int GetNumTextures() { return m_textures_used; }

	void AddTextureArray(const std::string& id, int width, int height);
	void AddTexture(const std::string& id, const std::string& filePath);

	void Bind();
	void Unbind() const;

	std::vector<int> GetSize(const std::string& filePath);
private:
	class TextureArray
	{
	public:
		TextureArray(int width, int height, unsigned int num_textures=2048);
		~TextureArray();

		void AddTexture(const std::string& filePath);

		void Bind(unsigned int slot = 0);
		void Unbind();
	private:
		unsigned int m_buffer;

		int m_width;
		int m_height;
		int m_BPP;
		unsigned int m_num_textures;
		unsigned int m_added_textures;
	};
private:
	std::vector<std::pair<std::string, TextureArray*>> m_texture_arrays;
	unsigned int m_textures_used;
};

