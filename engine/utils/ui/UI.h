#pragma once

#include "engine/includes.h"
#include "engine/rendering/Renderable.h"
#include "engine/rendering/Renderer.h"
#include "engine/resources/shaders/Shader.h"
#include "engine/resources/textures/Texture.h"

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class UI : public Renderable
{
public:
	UI();
	~UI();

    void RenderText(const std::string& text, float x, float y, float scale, glm::vec3 color);
private:
    std::map<char, Character> Characters;
    Shader m_shader;
    unsigned int VAO;
    unsigned int VBO;
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
};

