#include "Texture.h"

Texture::Texture() 
	: m_width(0), m_height(0), m_buffer(0), m_is_loaded(false)
{

}

Texture::Texture(GLenum sformat, GLenum dformat, const std::string& filepath)
	: m_width(0), m_height(0), m_buffer(0), m_is_loaded(false)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* tex_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bpp, STBI_rgb_alpha);
	if (!tex_data)
	{
		std::cout << "\nError: Failed to load texture" << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
		__debugbreak();
	}
	else
	{
		LoadData(sformat, dformat, m_width, m_height, tex_data);
		stbi_image_free(tex_data);
	}
}

Texture::Texture(GLenum sformat, GLenum dformat, int width, int height, unsigned char* pixels)
	: m_width(width), m_height(height), m_buffer(0), m_is_loaded(false)
{
	LoadData(sformat, dformat, m_width, m_height, pixels);
}

Texture::~Texture()
{
	if (m_is_loaded)
	{
		glDeleteTextures(1, &m_buffer);
	}
}

void Texture::LoadData(GLenum sformat, GLenum dformat, int width, int height, unsigned char* data)
{
	m_width = width;
	m_height = height;

	glGenTextures(1, &m_buffer);
	glBindTexture(GL_TEXTURE_2D, m_buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, sformat, m_width, m_height, 0, dformat, GL_UNSIGNED_BYTE, data);

	m_is_loaded = true;
}

void Texture::Bind(unsigned int slot)
{
	glBindTexture(GL_TEXTURE_2D, m_buffer);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::GetWidth()
{
	return m_width;
}

int Texture::GetHeight()
{
	return m_height;
}

GLuint Texture::GetTextureID()
{
	return m_buffer;
}

TextureAtlas::TextureAtlas(GLuint& buffer, int width, int height, int id)
	: m_buffer(buffer), m_width(width), m_height(height), m_ID(id), m_xoffset(0.0f), m_yoffset(0.0f), m_max_height_in_row(0.0f)
{
}

TextureAtlas::~TextureAtlas()
{
	glDeleteTextures(1, &m_buffer);
}

bool TextureAtlas::PreAddTexture(int width, int height)
{
	// Cannot exceed further in x direction and y direction
	return (!((m_xoffset + width >= m_width) && (m_yoffset + height >= m_height)));
}

TextureUse TextureAtlas::AddTexture(GLenum sformat, GLenum dformat, int width, int height, unsigned char* data, const std::string& th_name)
{
	// Cannot exceed further in x direction
	if (m_xoffset + width >= m_width)
	{
		// Creates new row
		m_xoffset = 0.0f;
		m_yoffset += m_max_height_in_row;
		m_max_height_in_row = height;
	}
	// Can exceed in x direction
	else
	{
		if (height > m_max_height_in_row)
		{
			m_max_height_in_row = height;
		}
	}

	glBindTexture(GL_TEXTURE_2D_ARRAY, m_buffer);
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, m_xoffset, m_yoffset, m_ID, width, height, 1, dformat, GL_UNSIGNED_BYTE, data);

	m_xoffset += width;

	std::vector<std::pair<float, float>> outTextureCords{ {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} };
	outTextureCords[0].first = (m_xoffset - width) / m_width; outTextureCords[0].second = 1.0f - ((m_yoffset + height) / m_height);
	outTextureCords[1].first = (m_xoffset) / m_width; outTextureCords[1].second = 1.0f - ((m_yoffset + height) / m_height);
	outTextureCords[2].first = (m_xoffset) / m_width; outTextureCords[2].second = 1.0f - ((m_yoffset) / m_height);
	outTextureCords[3].first = (m_xoffset - width) / m_width; outTextureCords[3].second = 1.0f - ((m_yoffset) / m_height);

	return TextureUse{ outTextureCords, m_ID, th_name };
}

bool TextureAtlas::PreAddTexture(const std::string& filepath, float scale)
{
	int width, height, channels;
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

	// Data is invalid
	if (!data)
	{
		std::cout << "Failed to load texture file " << filepath << std::endl;
		return false;
	}
	// Checks if space is available
	else
	{
		return PreAddTexture(width * scale, height * scale);
	}
}

TextureUse TextureAtlas::AddTexture(const std::string& filepath, const std::string& th_name, float scale)
{
	int width, height, channels;
	
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

	// Cannot exceed further in x direction
	if (m_xoffset + width > m_width)
	{
		// Creates new row
		m_xoffset = 0.0f;
		m_yoffset += m_max_height_in_row;
		m_max_height_in_row = height;
	}
	// Can exceed in x direction
	else
	{
		if (height > m_max_height_in_row)
		{
			m_max_height_in_row = height;
		}
	}

	glBindTexture(GL_TEXTURE_2D_ARRAY, m_buffer);
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, m_xoffset, m_yoffset, m_ID, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	m_xoffset += width;

	stbi_image_free(data);


	std::vector<std::pair<float, float>> outTextureCords{ {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} };
	outTextureCords[0].first = (m_xoffset - width) / m_width; outTextureCords[0].second = 1.0f - ((m_yoffset + height) / m_height);
	outTextureCords[1].first = (m_xoffset        ) / m_width; outTextureCords[1].second = 1.0f - ((m_yoffset + height) / m_height);
	outTextureCords[2].first = (m_xoffset        ) / m_width; outTextureCords[2].second = 1.0f - ((m_yoffset		 ) / m_height);
	outTextureCords[3].first = (m_xoffset - width) / m_width; outTextureCords[3].second = 1.0f - ((m_yoffset		 ) / m_height);

	return TextureUse{ outTextureCords, m_ID, th_name };
}

void TextureAtlas::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_buffer);
}

int TextureAtlas::GetID()
{
	return m_ID;
}

GLuint TextureAtlas::GetBuffer()
{
	return m_buffer;
}

TextureHandler::TextureHandler(int width, int height, const std::string& name)
	: m_atlas_width(width), m_atlas_height(height), m_buffer(0), m_name(name)
{
}

TextureHandler::~TextureHandler()
{
	for (auto& atlas : m_textureAtlases) 
	{
		delete(&atlas);
	}
}

void TextureHandler::Init()
{
	glGenTextures(1, &m_buffer);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_buffer);
		
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_BGRA, m_atlas_width, m_atlas_height, 500, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	m_textureAtlases.push_back(new TextureAtlas(m_buffer, m_atlas_width, m_atlas_height, m_textureAtlases.size()+1));
}

TextureUse TextureHandler::AddTexture(GLenum sformat, GLenum dformat, int width, int height, unsigned char* data)
{
	// Add a texture
	if (!m_textureAtlases.back()->PreAddTexture(width, height))
	{
		// If returns false, add new atlas
		m_textureAtlases.push_back(new TextureAtlas(m_buffer, m_atlas_width, m_atlas_height, m_textureAtlases.size() + 1));
	}

	return m_textureAtlases.back()->AddTexture(sformat, dformat, width, height, data, m_name);
}

TextureUse TextureHandler::AddTexture(const std::string& filepath, float scale)
{
	// Add a texture
	if (!m_textureAtlases.back()->PreAddTexture(filepath, scale))
	{
		// If returns false, add new atlas
		m_textureAtlases.push_back(new TextureAtlas(m_buffer, m_atlas_width, m_atlas_height, m_textureAtlases.size() + 1));
	}

	return m_textureAtlases.back()->AddTexture(filepath, m_name, scale);
}

TextureUse TextureHandler::FullTexture(int textureID)
{
	std::vector<std::pair<float, float>> outTextureCords{ {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} };

	outTextureCords[0].first = 0.0f; outTextureCords[0].second = 0.0f;
	outTextureCords[1].first = 1.0f; outTextureCords[1].second = 0.0f;
	outTextureCords[2].first = 1.0f; outTextureCords[2].second = 1.0f;
	outTextureCords[3].first = 0.0f; outTextureCords[3].second = 1.0f;

	return TextureUse{ outTextureCords, textureID };
}

void TextureHandler::Bind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_buffer);
}
