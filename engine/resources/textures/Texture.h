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
    Texture(GLenum sformat, GLenum dformat, const std::string& filepath);
    Texture(GLenum sformat, GLenum dformat, int width, int height, unsigned char* pixels);
    ~Texture();

    void LoadData(GLenum sformat, GLenum dformat, int width, int height, unsigned char* data);

    void Bind(unsigned int slot=0);
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
    float m_texture_id;
    std::string th_name;
};

class TextureAtlas
{
public:
    TextureAtlas(GLuint& buffer, int width, int height, int id);
    ~TextureAtlas();

    bool PreAddTexture(int width, int height);
    TextureUse AddTexture(GLenum sformat, GLenum dformat, int width, int height, unsigned char* data, const std::string& th_name);

    bool PreAddTexture(const std::string& filepath, float scale=1.0f);
    TextureUse AddTexture(const std::string& filepath, const std::string& th_name, float scale=1.0f);
    
    void Bind();
    int GetID();

    GLuint GetBuffer();
private:
    GLuint m_buffer;
    float m_width, m_height;
    float m_xoffset, m_yoffset, m_max_height_in_row;
    int m_ID;
};

class TextureHandler {
public:
    TextureHandler(int width, int height, const std::string& name);
    ~TextureHandler();

    // Add first atlas
    void Init();

    // Add a texture to the last texture atlas
    TextureUse AddTexture(GLenum sformat, GLenum dformat, int width, int height, unsigned char* data);
    TextureUse AddTexture(const std::string& filepath, float scale=1.0f);

    TextureUse FullTexture(float textureID);

    //void RemoveTexture(int texID);

    void Bind();
private:
    GLuint m_buffer;

    std::vector<TextureAtlas*> m_textureAtlases;
    float m_atlas_width, m_atlas_height;

    std::string m_name;
};