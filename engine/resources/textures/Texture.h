#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/stbi_image/stb_image.h"
#include "dependancies/glm/glm.hpp"

#include "engine/resources/shaders/Shader.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Texture 
{
public:
    Texture();
    Texture(const std::string& filepath);
    Texture(int width, int height, unsigned char* pixels);
    ~Texture();

    void LoadData(unsigned char* data);

    void Bind();
    void Unbind();

    int GetWidth();
    int GetHeight();
    GLuint GetTextureID();
private:
    GLuint m_buffer;

    int m_width;
    int m_height;
    int m_bpp;

    bool m_is_loaded;
};

struct TextureUse
{
    std::vector<std::pair<float, float>> m_tex_cords;
    int m_texture_id;
};

class TextureAtlas
{
public:
    TextureAtlas(GLuint& buffer, int width, int height, int id);
    ~TextureAtlas();

    bool PreAddTexture(const std::string& filepath);
    TextureUse AddTexture(const std::string& filepath);
    
    void Bind();
    int GetID();
private:
    GLuint m_buffer;
    float m_width, m_height;
    float m_xoffset, m_yoffset, m_max_height_in_row;
    int m_ID;
};

class TextureHandler {
public:
    TextureHandler(int width, int height);
    ~TextureHandler();

    // Add first atlas
    void Init();

    //void AddTexture(int width, int height, unsigned char* data, int texID);
    //bool AddTexture(const std::string& filepath, int& textureID);

    // Add a texture to the last texture atlas
    TextureUse AddTexture(const std::string& filepath);

    //void RemoveTexture(int texID);

    void BindTexture(int textureID);
private:
    GLuint m_buffer;

    std::vector<TextureAtlas*> m_textureAtlases;
    float m_atlas_width, m_atlas_height;
};