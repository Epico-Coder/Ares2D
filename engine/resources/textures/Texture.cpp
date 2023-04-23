#include "Texture.h"
#include "dependancies/stbi_image/stb_image.h"
#include <iostream>

TextureHandler::TextureHandler()
{
}

TextureHandler::~TextureHandler()
{
	for (auto tex_array : m_texture_arrays)
		delete(tex_array.second);
}

void TextureHandler::AddTextureArray(const std::string& id, int width, int height)
{
	m_texture_arrays.push_back(std::make_pair(id, new TextureArray(width, height)));
	m_textures_used++;
}

void TextureHandler::AddTexture(const std::string& id, const std::string& filePath)
{
	for (auto pair : m_texture_arrays)
	{
		if (pair.first == id)
		{
			pair.second->AddTexture(filePath);
		}
	}
}

void TextureHandler::Bind()
{
	for (int i = 0; i < m_texture_arrays.size(); i++)
	{
		m_texture_arrays[i].second->Bind(i+1);
	}
}

void TextureHandler::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

std::vector<int> TextureHandler::GetSize(const std::string& filePath)
{
	int width, height, BPP;
	stbi_load(filePath.c_str(), &width, &height, &BPP, STBI_rgb_alpha);
	return std::vector<int>{width, height};
}

TextureHandler::TextureArray::TextureArray(int width, int height, unsigned int num_textures)
{
	m_width = width;
	m_height = height;
	m_BPP = 4;
	m_num_textures = num_textures;
	m_added_textures = 0;

	glGenTextures(1, &m_buffer);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_buffer);

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_BGRA, m_width, m_height, m_num_textures, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

TextureHandler::TextureArray::~TextureArray()
{
	glDeleteTextures(1, &m_buffer);
}

void TextureHandler::TextureArray::AddTexture(const std::string& filePath)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* tex_data = stbi_load(filePath.c_str(), &m_width, &m_height, &m_BPP, STBI_rgb_alpha);
	if (!tex_data)
	{
		std::cout << "\nError: Failed to load texture" << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
		__debugbreak();
	}
	else
	{
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_added_textures, m_width, m_height, 1, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
		m_added_textures++;
		stbi_image_free(tex_data);
	}
}

void TextureHandler::TextureArray::Bind(unsigned int slot)
{
	glBindTextureUnit(slot, m_buffer);
}

void TextureHandler::TextureArray::Unbind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

Texture::Texture(int width, int height)
{
	glGenTextures(1, &m_buffer);
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_buffer);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getID() const
{
	return m_buffer;
}
